# subnetting
为什么要有子网这个概念.  
1. 维护一个大的网络,是一个很复杂的事情.  
2. 我们想要有一些权限的管理,比如一个子网不能访问另外一个子网.  
上面说的都是子网的优点.缺点是什么呢?之前我们将,ip+port的方式,一个请求过来需要找到network号,host号和process.现在,分为了子网,那么中间就要加一个,寻找network,寻找子网,寻找host,寻找process.但是这和子网的优点相比,代价很小.

## 如何划分子网  
如果是一个c类网络,也就是24位networkId,8位hostid的.networkid我们只能将256-2 的hostid分为子网.我们如果选择8位中的第一位,那么我们就可以划分为2两个子网,然后浪费4个hostid,因为每个子网要浪费2个hostid.如果我们选择2位划分,就划分了4个子网,浪费了8个hostid.  
子网掩码: 子网掩码是和ip地址进行运算的,每个位置进行与运算,所得到的结果就是这个ip地址所属于的子网号,然后就可以把这个数据包发送给这个子网了.  
例如,如果子网掩码是255,255,255,128. 那么就是11111111.11111111.11111111.10000000.这样,一个网络请求过来,ip是192.168.1.132 它和子网掩码进行运算的结果是192.168.1.128.也就是这个网络请求,要发送到128所在的那个子网.这个过程,是在C类网络内部的路由器中进行的.外部网络,发现这个网络请求是这个networkid所代表的网络,就把数据包发送过来.而在这个网络内部,通过子网掩码,进行寻找应该把这个数据包发送到哪一个网络上面.