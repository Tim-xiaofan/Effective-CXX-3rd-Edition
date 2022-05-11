#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::shared_ptr;
using std::vector;

void foo(void){}

template<typename T>
void dump(const T & t){}
#define  IDER_DEBUG 1
#define FUNC_TRAC(info) {if(IDER_DEBUG)cout<<"----"<<info<<"----"<<endl;}

int main(int argc, char *argv[])
{
	/** book*/
	{
        class Base 
		{
		public:
			virtual ~Base(){}
			virtual void foo(void){cout << "Base::foo is called\n";}
		};
        class Derived: public Base
		{
		public:
			virtual ~Derived(){}
			virtual void foo(void){cout << "Derived::foo is called\n";}
		};
        Derived d;
        Base *pb = &d;// implicitly convert Derived* → Base *
		Derived *pd = &d;
		cout << "Base addr : " << (void *) pb << endl;
		cout << "Derived addr : " << (void *) pd << endl;

		/**  Here's a way to implement this that looks like it 
		  does the right thing, but doesn't*/
        // base class
        class Window
        {
        public:
            // base onResize impl
            virtual void onResize() {_h *=2; _w *=2;}
			Window(int h=255, int w=255):_h(h),_w(w){}
			virtual void dumpSize(void)const
			{
				cout << "<" <<  _h << "," << _w << ">" << endl;
			}
		protected:
			int _h, _w;
        };

        // derived class
        class SpecialWindow : public Window
        {
        public:
            // derived onResize impl;
            virtual void onResize()
            {
                /** cast*this to Window, does not invoke that 
				  function on the current object*/
				dumpSize();
                static_cast<Window>(*this).onResize();
				dumpSize();
				/** solution*/
				Window::onResize();
				dumpSize();
            }
			void blink(){ cout << "SpecialWindow::blink" << endl;}
        };
		SpecialWindow sw;
		sw.onResize();


		/** 在需要性能的代码中，避免使用dynamic_cast，
		  因为dynamic_cast需要付出较高的性能损耗。*/
		{//solution:use contauiners(e.g:smart pointers)

			cout << "\n\n*****dynamic_cast suggestion*****" << endl;
			{
				/** not recommended*/
				cout << ">>not recommended" << endl;
				typedef std::vector<std::shared_ptr<Window> > VPW;
				VPW winPtrs;
				winPtrs.push_back(shared_ptr<Window>(new SpecialWindow()));
				winPtrs.push_back(shared_ptr<Window>(new Window()));
				SpecialWindow * psw = nullptr;
				for(VPW::iterator it = winPtrs.begin(); it != winPtrs.end(); ++it)
				{
					if((psw = dynamic_cast<SpecialWindow*>(it->get())))
					  psw->blink();
				}
			}
			{ 
				/** recommended: but this approach won't allow you to store 
				  pointers to all possible Window derivatives in the 
				  same container*/
				cout << ">>solution1" << endl;
				typedef vector<shared_ptr<SpecialWindow>> VPSW;
				VPSW winPtrs;
				winPtrs.push_back(shared_ptr<SpecialWindow>(new SpecialWindow()));
				winPtrs.push_back(shared_ptr<SpecialWindow>(new SpecialWindow()));
				for (VPSW::iterator iter = winPtrs.begin();
							iter != winPtrs.end();// better code: uses no dynamic_cast
							++iter)
				  (*iter)->blink();
			}
			{//moving virtual functions up the hierarchy
				cout << ">>solution2" << endl;
				class Window1
				{
					public:
						virtual void blink(){}
				};
				class SpecialWindow1:public Window1
				{
					public:
						virtual void blink(){cout << "SpecialWindow1::blink" << endl;}
				};
				typedef vector<shared_ptr<Window1> > VPW;
				VPW winPtrs;
				winPtrs.push_back(shared_ptr<Window1>(new SpecialWindow1()));
				winPtrs.push_back(shared_ptr<Window1>(new Window1()));
				for (VPW::iterator iter = winPtrs.begin();
							iter != winPtrs.end();// better code: uses no dynamic_cast
							++iter)
				  (*iter)->blink();
			}
		}
    }

	/** more*/
    /** C-style 类型转换 */

	{
		cout << "\n\n*****C-style cast*****" << endl;
    	int i = int(3.14);
    	int i1 = (int)3.14;
    	cout << "i = " << i << endl;
    	cout << "i1 = " << i1 << endl;

    	/** C++-style 类型转换*/
    	/**
    	 * const_cast
    	 * 
    	 * 可以使用表达式 const_cast<T>(v) 更改指针或引用的 const 或 volatile 限定符。
    	 * （在新式强制类型转换中，只有 const_cast<> 可以删除 const 限定符。）
    	 * T 必须是指针、引用或指向成员的指针类型。
    	 * */
    	const volatile int *cvip = &i;
    	int *ip = const_cast<int *>(cvip);// remove const and volatile
		dump(ip);
	}

    /** 
     * reinterpret_cast可以在任意指针之间进行互相转换，即使这些指针所指的内容是毫无关系的，
     * 也就是说一下语句，编译器是不会报错的，但是对于程序来说也是毫无意义可言的，
     * 只会造成程序崩溃
     * 
     * 表达式 reinterpret_cast<T>(v) 用于更改对表达式 v 值的解释。
     * 该表达式可用于在指针和整型之间，在不相关的指针类型之间，在指向成员的指针类型之间，
     * 和在指向函数的指针类型之间转换类型。
     * 
     * 使用 reinterpret_cast 运算符可能会得到未定义的结果或实现相关结果。
     * 以下几点描述了唯一确定的行为：
     * 
     * 1.从指针类型到一个足够大的整数类型
     * 
     * 2.从整数类型或者枚举类型到指针类型
     * 
     * 3.从一个指向函数的指针到另一个不同类型的指向函数的指针
     * 
     * 4.从一个指向对象的指针到另一个不同类型的指向对象的指针
     * 
     * 5.从一个指向类函数成员的指针到另一个指向不同类型的函数成员的指针
     * 
     * 6.从一个指向类数据成员的指针到另一个指向不同类型的数据成员的指针
     * 
     * 7.在所有允许的情况下，空指针类型转换为不同的空指针类型后仍然是空指针。
     * 
     * 8.reinterpret_cast 运算符不能用来删除 const，可使用 const_cast 来实现。
     * 
     * 9.reinterpret_cast 运算符不能用来在指向同一类分层结构中不同类的指针之间进行转换，
     * 可使用静态或动态强制类型转换来实现。（reinterpret_cast 不执行所需的调整。）
     * */
    {
        class A {int a; public: A(){} void foo(void){}};
        class B: public A {int b, c;};
        class C{public: void foo(void){}};
        A a1;
        long l = reinterpret_cast<long>(&a1); // 情况1
        A* ap = reinterpret_cast<A*>(l);      // safe，情况2
        B* bp = reinterpret_cast<B*>(&a1);    // unsafe，情况9
		dump(bp);

        const A a2;
        //ap = reinterpret_cast<A*>(&a2);  // error, const removed，情况7

        C * cp = reinterpret_cast<C*>(ap); //safe，情况4
		dump(cp);

        typedef void(*func1_t)(void);
        typedef void(*func2_t)(int, int);
		func1_t f1 = foo;
		func2_t f2 = reinterpret_cast<func2_t>(f1);// safe, case 2
		dump(f2);

		typedef void (A::*Afoo_t)(void);
		typedef void (C::*Cfoo_t)(void);
		Afoo_t Afoo = &A::foo; // use & to asign
		Cfoo_t Cfoo = reinterpret_cast<Cfoo_t>(Afoo);// OK, case 5
		dump(Cfoo);
    }

    /** 
     * 参考：https://www.cnblogs.com/ider/archive/2011/07/31/cpp_cast_operator_part4.html
     * static_cast和reinterpret_cast一样，在面对const的时候都无能为力：两者都不能去除
     * const限定。两者也存在的很多的不同，比如static_cast不仅可以用在指针和引用上，还可以
     * 用在基础数据和对象上；前面提到过reinterpret_cast可以用在"没有关系"的类型之间，而用
     * static_cast来处理的转换就需要两者具有"一定的关系"了。
     * 
     * 1. 对于static_cast所需要的关系，"继承"绝对是其中之一，所以static_cast支持指向
     * 基类的指针和指向子类的指针之间的互相转换
     * 
     * 2. 实际上static_cast真正用处并不在指针和引用上，而在基础类型和对象的转换上 。 
     * 而基于基础类型和对象的转换都是其他三个转换运算符所办不到的。
     * 
     * 3.从上边对static_cast分析可以跟看，static_cast跟传统转换方式几乎是一致的，所以只要将
     * static_cast和圆括号去掉，再将尖括号改成圆括号就变成了传统的显示转换方式
     * */
    {
        class Parents
        {
        public:
            virtual ~Parents() {}
            /*codes here*/
        };

        class Children : public Parents
        {
            /*codes here*/
        };
        /** case 1*/
        Children * daughter = new Children();// 派生类--》基类
	    Parents * mother = static_cast<Parents*> (daughter); //right, cast with polymorphism
		dump(mother);
	    Parents * father = new Parents();//基类--》派生类
	    Children * son = static_cast<Children*> (father); //no error, but not safe
		dump(son);
        /** case 2*/
        float floatValue = 21.7;
        int intValue = 7;
        cout << floatValue / 7 << "\t\t" << static_cast<int> (floatValue)/7 <<endl;
        cout << intValue/3 << "\t\t" << static_cast<double> (intValue)/3 << endl;
        /** 对于对象的转换，也是需要又关系的，这层关系就是C++用户自定义类型转换中提到的方法：
         * 构造函数（Constructor）
         * 类型转换运算符（Type –Cast Operator）
         * */
        //class declaration
        class D
        {
        public:
            D(double d) : _d(d) {}

            operator int() const
            {/* “(int)D”类型转换 */
                std::cout << "(int)d called!" << std::endl;
                return static_cast<int>(_d);
            }

        private:
            double _d;
        };
		class F
		{
		public:
			F(float f) : _f(f){}
			F(const D & d)
			{
				cout << "F(const D & d) called" << endl;
				_f = 0.123456 * long(&d);
			}
            operator float() const
            {/* “(float)F”类型转换 */
                return static_cast<float>(_f);
            }
		private:
			float _f;
		};
        D d = 3.14;
		int i = static_cast<int>(d);
		cout << "i = " << i << endl;
		F f = static_cast<F>(d);
		cout << static_cast<float>(f) << endl;
    }

    /** dynamic_cast运算符，应该算是四个里面最特殊的一个，因为它涉及到编译器的属性设置，而且
     * 牵扯到的面向对象的多态性跟程序运行时的状态也有关系，所以不能完全的使用传统的转换方式来
     * 替代。但是也因此它是最常用，最不可缺少的一个运算符。
     * 
     * 1. 与static_cast一样，dynamic_cast的转换也需要目标类型和源对象有一定的关系：继承关系。
     * 更准确的说，dynamic_cast是用来检查两者是否有继承关系。因此该运算符实际上只接受基于
     * 类对象的指针和引用的类转换。
     * */
    {
		cout << "\n\n*****dynamic_cast*****" << endl;
        class A
        {//base class
			public:
				A()=default;
				virtual ~A(){}
				virtual void foo(void)
				{
					cout << "A::foo" << endl;
				}
        };
		class B:public A
		{//derived class
		public:
			B():A(){}
			virtual ~B(){}
			virtual void foo(void)
			{
				cout << "B::foo" << endl;
			}
			void foo1(void)
			{
				cout << "B::foo1" << endl;
			}
		};
		class C
        {
			public:
				C()=default;
				virtual ~C(){}
				virtual void foo(void)
				{
					cout << "C::foo" << endl;
				}
        };
		/**  convert derived class to base class*/
		cout << ">>implicit cast derived class to base clas" << endl;
		A * a = new B();//implicit convertion, OK
		a->foo();//B::foo called 
		
		cout << ">>dynamic_cast derived class to base class" << endl;
		a = dynamic_cast<A*>(new B);
		a->foo();//B::foo called
		
		cout << "static_cast from derived class to base class" << endl;
		a = static_cast<A*>(new B);
		a->foo();//B::foo called;
		
		/** convert base class to derived*/
		cout << "dynamic_cast from base class to derived class" << endl;
		B * b = dynamic_cast<B*>(new A());
		cout << "b = " << (void *)b << endl;
		
		cout << "static_cast from base class to derived class" << endl;
		b = static_cast<B*>(new A());
		cout << "b = " << (void *)b << endl;
		if(b) b->foo1();//error
    }
    return 0;
}

/**
 * https://www.cnblogs.com/ider/archive/2011/08/05/cpp_cast_operator_part6.html
 * 结合网络上各个站点看到的关于C++转换符的知识，以及前面那些文章得到的反馈，可以将各个转换运算符的
 * 使用总结如下：
 * 
 * 对于传统的转换方式(C式或函数式)，只在数值类型（包括整型、浮点型、字符类型和枚举）上使用。
 * 这也是延续C的形式，当然这类转换也是可以用static_cast来替换，但是因为是基本类型，所以传统转换已经很直观。
 * 
 * 对于const_cast转换运算符，用在需要去除掉const限定的时候。其实这种情况出现的很少，可能的
 * 方法在const_cast一文中已经又举例，不过还是反复强调， 使用const_cast转换后，绝对不可
 * 试图修改结果的值。
 * 
 * 对于reinterpret_cast转换运算符，一般用在将对象指针类型转换到整数类型或者void * 
 * （空指针）。如同在文中举出的隐患，因此注意的是，若要使用其结果，一定要将类型转换回去后使用。也不要将随意的整数转换成指针类型。
 * 
 * 对于static_cast转换运算符，将其用在对象的转换之上（虽然static_cast也可以用在有继承关系的类型指针之间，
 * 但是还是将这方面的转换交给dynamic_cast来操作吧）， static_cast会调用相应的构造函数或者重载的转换运算符。
 * 
 * 通过文章的留言反馈，以及Google C++ Style Guide的推荐格式，知道对于单参构造函数的存在可能
 * 会引发一些隐式的转换，因此用static_cast也可以明确的指出类型的转换过程，避免生成多余的临时对象造成效率下降。
 * 
 * 对于dynamic_cast转换运算符，将其用在具有继承关系的指针类型之间的转换。无论是从基类到子类
 * 的转换，还是子类到基类的转换，都将dynamic_cast套上去，也算是标识它们是一家子。
 * */
