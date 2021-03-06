# 开放封闭原则  OCP

软件实体(类,模块,函数)应该是可以扩展的,但是不可以修改的.  
如果程序的一个改动就引起了连锁的反应,导致了相关模块的改动,那么设计就有僵尸性.如果能够正确的应用开放封闭原则,那么在进行同样的修改时,只用添加代码,不用改动正常运行的代码.  

1. 对于扩展是开放的.  --> 利用多态.
2. 	对于更改是封闭的.  --> 利用接口.

## 关键是抽象  
面向对象的设计语言,可以创建一组任意可能行为的抽象体,就是接口.  
模块可以操作一个接口,由于模块依赖的是一个固定的抽象体,所以它对于修改是关闭的.但是,可以通过从这个抽象体进行派生,也可以扩展这个模块的行为.     

**例子**   
Client --> Server 客户类直接引用服务器类,如果想要更换服务器,必须要更改新的服务器类.如果新的服务器类的接口还和之前的不一样,所以出错的地方都要改.  
Client --> ClientInterface,Server实现这个接口. 如果要更换服务器,更换实现,但是客户和服务器打交道的代码是依赖接口的,接口不用改变.
	
	
## 举例, Shape

```
enum ShapeType {square, circle}

void DrawAllSahpes(list,n) {
	for (int i = 0; i < n; i++) {
		value = list[i];
		switch(value.type){
			case square: drawSquare(value);break;
			case circle: drawCircle(value);break;
			default:
		}
	}
}

```  
上面的代码不符合开放封闭,在于,添加一个新的形状,要修改switch的代码,要添加shapeType的定义.而且,这种ifelseswitch的代码可能会非常复杂.修改一个小地方,要整体的一个函数要随着改变.所有的地方重新编译.并且,判断的工作放在了一起,相当于把根据类型做操作的判断集中到了一起,而根据多态,自动分散到了各个类中.   
上面的修改成为开放封闭的很简单,增加shape抽象类,每一个派生类都实现draw方法,而在drawAllShape里面,调用抽象类的draw方法,根据多态动态的找到实现. 而这样,在增加新的类型的时候,也仅仅是增加新类型的实现.原来的主方法的代码根据接口实现的,不用改变.同时,也避免了大量逻辑操作.   

但是也不是万能的,如果要修改的是drawAllShape的逻辑,就是要修改之前的代码.比如,先画圆后画square.这样,之前的抽象反而是坑.因为c++没有办法知道实际类型啊,当然后面有了dynamic转化,但是还是麻烦,这样,倒不如最初的enum值得判断了.  
开放封闭,要抉择什么开放什么关闭.同时,建立抽象层也是一件会增加逻辑复杂的事情.并不是万能的.随便放置挂钩,反而让程序过度设计,为了维护这些挂钩,让每次编写功能痛苦无比.  


### 挂钩放置   
1. 只受一次愚弄  
	最初编码的时候,假设变化不发生,当变化发生时,利用抽象隔离同类的变化.
2. 刺激变化   
	尽量早的知道,可能发生的变化. 核心一点就是早点出迭代版本,让需求早点明确.纳尼???
	
### 举例, 利用抽象实现绘画顺序变化的封闭
  
  在shape抽象类里面,增加bool precede(Shape *value)接口,他的功能就是排序的时候传入的判断谁先谁后的那个block,而在drawAllShape的实现里面,首先对array进行一次排序,排序的具体依据,通过precede的接口返回值.但是precede怎么实现呢,如果判断类型,通过dynamicCast,那又变成了通过逻辑判断实现的代码,如果增加了新的类型,每个类的precede又要修改了. 作者给出的答案是,一个静态表里面,存放谁先谁后的顺序,precede的代码,就是读取自己类在表中的位置,根据存储的位置,判断先后.这样,修改点就只在新生类和新生类注册自己到表结构里了.不封闭的是表结构,但是代码封闭了. 
  
### 如何做到

需求总是变化的，面对变化，一个优秀的程序（类，组件）应该是通过扩展来适应新的变化，而不是通过修改
另一方面，也就是说，当一个程序（类，组件）写好之后，就不应该再修改它的代码（bug不算）
如果违反了OCP，当你发现自己经常在改一个类/组件的源代码的时候，那这个类/组件应该也违反SPR了  

根据经典的设计模式思想，要做到OCP，最优的途径是：对抽象编程  
让类依赖抽象，当需要变化的时候，通过实现抽象来适应新的需求  
对抽象编程，是利用了另外两大原则：  
里氏代换原则（LSP，Liskov Substitution Principle）  
合成/聚合复用原则（CARP，Composite Aggregate Reuse Principle）
	