# String对象
## 概述 
String对象是JavaScript原生提供的三个包装对象之一，用来生成字符串的包装对象
```
var s1 = 'abc';
var s2 = new String('abc');
typeof s1 // "string"
typeof s2 // "object"
s2.valueOf() // "abc"
```
变量s1是字符串，s2是对象。由于s2是对象，所以有自己的方法，valueOf方法返回的就是它所包装的那个字符串。
实际上，字符串的包装对象是一个类似数组的对象（即很像数组，但是实质上不是数组）。
new String("abc")
// String {0: "a", 1: "b", 2: "c", length: 3}
除了用作构造函数，String对象还可以当作工具方法使用，将任意类型的值转为字符串。
String(true) // "true"
String(5) // "5"
上面代码将布尔值ture和数值5，分别转换为字符串。

## String.fromCharCode()
String对象提供的静态方法（即定义在对象本身，而不是定义在对象实例的方法），主要是fromCharCode()。该方法的参数是一系列Unicode码点，返回对应的字符串。
String.fromCharCode(104, 101, 108, 108, 111)
// "hello"
注意，该方法不支持Unicode码点大于0xFFFF的字符，即传入的参数不能大于0xFFFF。
上面代码返回字符的编号是0x0BB7，而不是0x20BB7。它的根本原因在于，码点大于0xFFFF的字符占用四个字节，而JavaScript只支持两个字节的字符。这种情况下，必须把0x20BB7拆成两个字符表示。
String.fromCharCode(0xD842, 0xDFB7)
// "𠮷"
上面代码中，0x20BB7拆成两个字符0xD842和0xDFB7（即两个两字节字符，合成一个四字节字符），就能得到正确的结果。码点大于0xFFFF的字符的四字节表示法，由UTF-16编码方法决定。

## 实例对象的属性和方法
### length属性
length属性返回字符串的长度。 
这里要注意的是字符串的长度是什么意思, JS中, 字符串是按照UTF-16的形式进行存储的, 而UTF-16是一种变长的unicode表示的方法, 对于unicode吗小于0XFFFF的字符, UTF-16是可以用两个字节进行存储的, 对于大于的, 就需要四个字节进行存储. 而JS中, 判断一个字符串的length属性的时候, 是用存储这个字符串的UTF-16的两个字节作为一个单位的. 所以, 对于上面的那个特殊的字, '𠮷', 其实在JS中, 是用了四个字节存储的, 这个时候, js返回的length是2, 虽然在我们看来, 这仅仅是1个汉字.   
### charAt()
charAt方法返回指定位置的字符，参数是从0开始编号的位置。这个函数, 返回的是两个字节的位置. ��, 对于𠮷这个字, 占用两个位置, 展示出来的字符是上面那两个, 也就是不可打印字符. 
这个方法完全可以用数组下标替代。如果参数为负数，或大于等于字符串的长度，charAt返回空字符串。

### charCodeAt()
charCodeAt方法返回给定位置字符的Unicode码点（十进制表示），相当于String.fromCharCode()的逆操作。
'abc'.charCodeAt(1) // 98
charCodeAt方法返回的Unicode码点不大于65536（0xFFFF），也就是说，只返回两个字节的字符的码点。如果遇到Unicode码点大于65536的字符，必需连续使用两次charCodeAt，不仅读入charCodeAt(i)，还要读入charCodeAt(i+1)，将两个16字节放在一起，才能得到准确的字符。

### concat()
concat方法用于连接两个字符串，返回一个新字符串，不改变原字符串。
该方法可以接受多个参数。
如果参数不是字符串，concat方法会将其先转为字符串，然后再连接。

### slice()
slice方法用于从原字符串取出子字符串并返回，不改变原字符串。
它的第一个参数是子字符串的开始位置，第二个参数是子字符串的结束位置（不含该位置）。
如果省略第二个参数，则表示子字符串一直到原字符串结束。
如果参数是负值，表示从结尾开始倒数计算的位置，即该负值加上字符串长度。

### substring(), substr()
substring方法用于从原字符串取出子字符串并返回，不改变原字符串。它与slice作用相同，但有一些奇怪的规则，因此不建议使用这个方法，优先使用slice。

### indexOf()，lastIndexOf()
这两个方法用于确定一个字符串在另一个字符串中的位置，都返回一个整数，表示匹配开始的位置。如果返回-1，就表示不匹配。两者的区别在于，indexOf从字符串头部开始匹配，lastIndexOf从尾部开始匹配。
它们还可以接受第二个参数，对于indexOf方法，第二个参数表示从该位置开始向后匹配；对于lastIndexOf，第二个参数表示从该位置起向前匹配。

### trim()
trim方法用于去除字符串两端的空格，返回一个新字符串，不改变原字符串。
该方法去除的不仅是空格，还包括制表符（\t、\v）、换行符（\n）和回车符（\r）。

### toLowerCase()，toUpperCase()
toLowerCase方法用于将一个字符串全部转为小写，toUpperCase则是全部转为大写。它们都返回一个新字符串，不改变原字符串。
这个方法也可以将布尔值或数组转为大写字符串，但是需要通过call方法使用。
String.prototype.toUpperCase.call(true)
// 'TRUE'
String.prototype.toUpperCase.call(['a', 'b', 'c'])
// 'A,B,C'

### match()
详见正则表达式  

### search()
search方法的用法等同于match，但是返回值为匹配的第一个位置。如果没有找到匹配，则返回-1。
详见正则表达式 

### replace()
replace方法用于替换匹配的子字符串，一般情况下只替换第一个匹配（除非使用带有g修饰符的正则表达式）。
详见正则表达式

### split()

split方法按照给定规则分割字符串，返回一个由分割出来的子字符串组成的数组。
'a|b|c'.split('|') // ["a", "b", "c"]
如果分割规则为空字符串，则返回数组的成员是原字符串的每一个字符。
'a|b|c'.split('') // ["a", "|", "b", "|", "c"]
如果省略参数，则返回数组的唯一成员就是原字符串。
'a|b|c'.split() // ["a|b|c"]
如果满足分割规则的两个部分紧邻着（即中间没有其他字符），则返回数组之中会有一个空字符串。
'a||c'.split('|') // ['a', '', 'c']
如果满足分割规则的部分处于字符串的开头或结尾（即它的前面或后面没有其他字符），则返回数组的第一个或最后一个成员是一个空字符串。
'|b|c'.split('|') // ["", "b", "c"]
'a|b|'.split('|') // ["a", "b", ""]
split方法还可以接受第二个参数，限定返回数组的最大成员数
'a|b|c'.split('|', 0) // []
'a|b|c'.split('|', 1) // ["a"]
'a|b|c'.split('|', 2) // ["a", "b"]
'a|b|c'.split('|', 3) // ["a", "b", "c"]
'a|b|c'.split('|', 4) // ["a", "b", "c"]
























