//
//  7_Function.h
//  BookNotes
//
//  Created by jansti on 2017/9/5.
//  Copyright © 2017年 jansti. All rights reserved.
//

#ifndef __Function_h
#define __Function_h


/*
    闭包
    当一个函数被调用的时候,会创建一个执行环境和相应的作用域链.然后使用arguments和其他的命名函数的值来初始化函数的活动对象.自己本身的活动对象位于链条的首位,
 外部函数的活动对象第二,依次直到全局执行环境的活动对象.
    函数的局部环境的变量对象,只会在函数执行的过程中存在.在创建函数的时候,会创建一个预先包含全局变量对象的作用域链,这个作用域链被保存在内部的[[Scope]]的属性中,
 当函数被调用的时候,会为函数创建一个执行环境,然后,通过复制函数的[(Scope)]属性中的对象构建起执行环境的作用域链.然后,被调用函数本身的变量对象被推入执行环境的作用域链,
 作用域链本质上是一个指向变量对象的指针列表而已.
    也就是说,创建函数的时候,它上级执行环境的变量对象形成了一个作用域链,被函数保存了起来.执行的时候,根据这个作用域链,构成执行环境的作用域链,并把自己添加到首位.
    在一个函数内部定义的函数会将外部函数的活动对象添加到自己的作用域中.因为内部函数的作用域链仍然引用着这个外部函数的活动对象,所以外部函数的活动对象仍然在内存中,直到
 内部函数也被销毁. 将被返回的内部函数设置为null,解除这个函数的引用.
    1. 闭包保存的是外部函数的整个变量对象,而不是某一个特殊的变量.所以,外部函数变量的变化,会在闭包运行时保存下来.
        例如 var a = 1; 闭包; a = 100; 闭包()的时候,a就是100.
    2. 函数在调用的时候,都会自动取得两个特殊变量:this 和 arguments.在搜索这两个变量的时候,只会搜索到自己的活动变量为止.因此,不可能直接访问外部函数的这两个变量.
 如果想要访问外部函数的this,只有把this保存在另外一个变量里面,然后让内部函数可以获取到这个缓存对象.
    var object = {
        name : "My object";
        getNameFucn : function() {
                    var that = this;
                    return function() {
                        return that.name;
                    }
        }
    }
    
 
    总结下为什么闭包可以访问保持捕获的值.外部函数创建了闭包之后,外部函数执行结束,但是外部函数的变量对象在内部函数的作用域链中,这个作用域链被存储在内部函数的[[scope]]的
 属性里面,因为有着这个引用的存在,外部函数在执行完之后,会销毁自己环境里面的作用域链,但是自己的变量因为变量对象存在内部函数的scope里,没有被释放.在内部函数运行的时候,会复制自己[scope]的作用域链到环境中,然后将自己本身的变量对象添加到环境的作用域链上,
 这样就可以访问到之前创建自己的外部函数的变量对象了.要想释放外部函数的变量对象,首先要释放内部函数.于是内部函数=null.切断内部函数的引用.
 
    3. 循环引用的问题
    
    function assignHandler() {
        var element = document.getElementById("someElement");
        var id = element.id;
        element.onClick = function() {
            alert(id);
        };
    }
 
    以上这段代码,最初是这样写的
    element.onClick = function() {
        alert(element.id);
    };
    按照oc的捕获原则,是会有循环引用的,element的block里面,有着element,而这个block又是element的一个属性.循环引用了,通过上面的var id = element.id,将id抽取出来,
使得block仅仅不过一个int值而不是整个element的对象,可以消除循环引用.
    但是这件事在js里面不能做到消除循环引用.因为闭包引用的是外部函数的整个变量对象.即使闭包不直接引用element,闭包也会引用外部函数的变量对象.所以,必须把element赋值为null.
 element = null;这里,将element 赋值 null.有什么意义呢.
    首先必须明确的是,assignHandler的变量对象,没有被释放.那么element和id这两个对象,是没有被释放的.如果它们被释放了,闭包怎么执行.但是,我们认为的在后面叫element的值赋值为
 null,就减少了element对于节点的引用.因为我们仅仅是希望获得里面的id值而已.在最后将element赋值为null,即使闭包还保存着外部函数的变量对象,里面的element为null,至少对应节点的
 引用已经认为的减少了.
 
 
    块级作用域
    没有块级作用域的概念,在块里面定义的变量,实际上是包含在函数里面而不是语句里面,所以for循环的i,实际是函数的变量而不是for里面的变量.
    多次重复声明变量不会造成变量值的改变,var a = 10; var a; a 还是10.var a = 10; var a = 100; a是100.因为后面的声明带了赋值语句.
    (function(){
        模拟块级作用域.其实,还是函数作用域,这是一个函数的作用域,函数声明后立马调用而已.这样的一个私有作用域,可以方位外部函数的作用域.是因为这个匿名函数,就是一个闭包,
        根据作用域链的寻找,外部环境的环境变量在闭包中存储着.这和之前c,oc,c++的规则其实不一样了.
    })();
    这种做法,1是可以防止在全局作用域里面定义变量的时候,向全局作用域注册太多的变量.
    2 是可以减少闭包的内存占用,因为没有引用指向这个匿名函数,匿名函数执行之后就销毁了,也销毁了存储的作用域链.
 
 
    私有变量.
    任何在函数的内部定义的变量,都可以认为是私有变量,不能在函数的外部访问.包括函数的参数,局部变量以及在函数内部定义的其他的函数.
    如果在函数内部建立一个闭包,闭包可以访问函数的私有变量了.把这个闭包传出去,就是可以访问函数内部私有变量的公开方法了.这种可以有权访问私有变量和私有函数的公有方法成为特权方法.
    1. 在构造函数里面编写特权方法.
    function MyObject() {
        var privateVariable = 10;
        function privateFunction() {
            return false;
        }
        
        this.publicMethod = function() {
            privateVariable ++'
            return privateFunction();
        }
    }
    利用私有和特权成员,可以隐藏那些不应该被直接修改的数据.
    funciton Person(name) {
        this.getName = function() {
            return name;
        }
        this.setName = function(value) {
            name = value;
        };
    }
    如果,name想要成为Person对象的属性,应该怎么做.this.name = name.但是没有调用this的赋值语句,name就是Person函数的一个私有变量.不过,this.getSetName里面,保存了一个
 闭包,在这个闭包里面,保存了对name的引用.于是,Person这个函数的变量对象,通过闭包可以存活,成为了person对象的私有变量.name在每一个实例里面都不一样,因为这是Person函数每次执行
 的时候都会创造不同的私有变量.
    2.静态私有变量
    上面的方法的问题在于,每次都要写方法的实现,但是方法应该是每个实例共享的.
     (function() {
        var privateVariable = 10;
        function privateFunction() {
            return false;
        }
        MyObject = function() {
        };
        MyObject.prototype.publicMethod = function() {
            privateVariable++;
            return privateFunction();
        }
    })();
    建造了构造函数和构造函数原型的公有方法.构造函数没有加var,代表这是一个全局对象.这样写,私有变量和函数是被所有的实例共享的.特权方法作为一个闭包,保持着这个匿名对象变量对象
 的引用.需要注意的是privateVariable是一个所有的实例公有的属性,相当于其他语言的static属性.
    3.模块模式.
    js是用对象字面量的方式创建单例对象的.
    var singleTon = {
        name : value,
        method : function() {
        }
    }
    为单例添加私有变量和特权方法
    var singleton = function() {
        
        var privateVariable = 10;
        funtion privateFunction() {
            return false;
        }
 
        return {
                    publicProperty: true;
                    publicMethos: function() {
                                privateVariable++;
                                return privateFunction();
                    }
 
                }
    }();
    这个模式返回的是一个匿名对象,匿名对象的公开接口里面,访问了函数的私有对象,但是我们在用这个匿名对象的时候,只能用它的公开接口.
    需要注意的是,这个公开接口是个闭包,它使得外部函数的变量对象存活.如果publicMethod只是指向一个内部变量的话,内部变量因为有引用能存活,其他的应该会被释放.
    
    问题,如何编写实例的私有变量然后将操作私有变量的方法注册到原型中去.
    做不到.    
    因为,上面实现的方法操作私有变量,很明确的一点就是,操作私有变量的方法,和这个私有变量是绑定在一起的.静态私有变量,在一个函数里面声明赋值,然后就在这个函数里面将
 操作这个私有变量的函数注册到了原型里面. 而平常的私有变量,在构造函数里面,声明赋值,然后在这个构造函数里面,给变量的实例赋值一个可以操作这个私有变量的函数.那么上面说
 的这两种函数,都是操作了某一个地方的私有变量.但是其实,这个私有变量和这个对象是没有关系的,这个私有变量并存在于这个对象的内存空间,它们仅仅是依靠闭包的特性在一起.
 既然如此,我们想要把一个方法注册到原型中,就只有一个私有变量可以操作了.
    那么其他的语言怎么做的这个事情,私有方法,通过this.privateVariable可以读取到对象里面存储的私有变量,这个私有变量就是这个对象的一个值.对象的分配内存的时候,初始化的
 时候,都给这个私有变量留空间留操作了.这和js有着很大的不一样.
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */


#endif /* __Function_h */
