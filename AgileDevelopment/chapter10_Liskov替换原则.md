### Liskov替换原则 --> 子类型必须能够替换调他们的基类型.  
若对每个类型S的对象o1,都存在一个类型T的对象o2,使得在针对T编写的程序中,用o1代替o2程序P的行为功能不变,那么s就是t的子类型.
开放封闭原则的主要机制是抽象和多态,在静态语言里面,支持抽象和多态的关键机制是继承,创建基类和派生类完成扩展.   
对于LSP的违反常常会导致开放封闭原则的违反.   
最明显的方式就是使用运行时类型识别.这种方法,常常使用一个明显的if或者switch语句进行对象类型的判断,然后通过类型调用不同的行为函数.这样做的缺点在于,在转化函数的内部,必须要知道所有的派生类,或者知道某个特殊的派生类,其他的做统一处理.然而这样做,很容易在引入新类的时候引起错误.例如,在这个转化后处理的过程中,没有加入新类的判断,而新类是需要特殊处理的,这种地方如果过多,弥漫在程序内部,久而久之,就不知道在这个地方应不应该做判断,判断后应该做什么处理.  
再有,如果加入一个新类就要修改之前所有的代码,明显违反开放封闭原则,代价太大.增加功能就有可能引起之前功能的错误.

### rectangle 和 square 
有一个长方形类,有setWidth和setHeight方法,然后有一个正方形类,重写了这两个方法.有一个f(Rectangle *pointer).在这个函数里面,调用setWidth和setHeight.
首先,这样的设计,是有可能出错的,那就是setWidth和setHeight并没有设置为虚函数.这在OC,或者JS里面不是问题,但是c++这种根据虚函数表实现多态的语言,如果不是虚函数,就调用标明类型的方法.问题是,Rectangle的设计者,怎么知道会有子类要覆盖这两个方法呢.不管怎么说,我们修改了.  
第二个问题更加隐蔽,那就是square的两个set方法,其实会影响另外一个数据,设置宽,高,在正方形看来,同时要影响宽高,而长方形是分别赋值的.那么,在f的使用者看来,传进来的是长方形,分别设置了宽高不同的值,那么应该取哪个值呢.这样看来,正方形替换了长方形之后,行为功能改变了,这违反了LSP规则.  
怎么会出现这样的问题呢,其实是square的类的实现,违反了rectangle的行为特性.rectangle的长短是独立变化的,square确实要求统一变化.  

**结论**  
一个模型,如果孤立的看,并不是具有真正意义的有效性,只能通过模型的使用程序来表现.设置者应该做出合理假设,用假设审视它.(用单元测试写在对于基类的测试程序里).但是,过多的假设,又会让程序变得过度设计.所以,只预测最明显的违反情况,直到出现问题,才去处理.  

is_a 是关于行为的.正方形在现实世界是长方形,但是从f函数的使用者来说,正方形绝不是长方形,因为正方形的行为方式和长方形的行为不相容.对象的行为模式才是真正关注的问题.
根据契约设计:基类设置必须要遵守的契约,派生类必须接受基类的一切.例如,基类设置了,setWidth之后,height不受改变,那么派生类就不能在setWidth中改变height.而这种检测,应该写到单元测试里面.    


### 结论
正是子类的可替换性,才使得使用基类类型的模块在无需修改的情况下就可以扩展.这种可替换性,是开发人员可以隐式依赖的东西.子类型的正确定义是可替换性的.

在编码层面,面向接口编程,可以让接口的使用者不改变逻辑,而通过增加新的实现类来实现新的功能.新的实现类,替换的是接口的实现方式,但是接口的调用方式,使用方式不用修改.这也是平时多态的意义所在.
然而,根据这个原则的定义,有些东西要重新考虑.  
1. 子类的行为要不要完全符合父类的行为. 上面的正方形和长方形是一个例子. 还有就是对于一个接口,子类在某些情况下,比如初始化不完全的时候崩溃,这算不算违反了父类的行为模式.至少在调用者看来,调用一个子类和另一个子类,达到的效果不一样了.
2. 我们要不要严格遵守这个规则. 如果严格遵守这个规则,那么正方形就不是长方形的子类,但是大部分情况下,正方形必须相等这件事的后果又没有那么严重.为了维护这个原则,去做很多抽象层的架构,使得代码结构越来越混乱,值不值得.





