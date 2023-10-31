Go有一个推荐的工作区布局，其中包含三个主要目录：src、pkg和bin。  
你的代码应该放在src目录下。  
例如，如果你有一个项目叫myproject，你可以在src下创建一个同名目录，并在该目录下放置你的包。  
```
workspace/  
├── bin/  
├── pkg/  
└── src/  
    └── myproject/  
        ├── main.go       # for the main package  
        └── mypackage/    # for your custom package  
            └── mypackage.go  
```

在main.go中，可以使用相对于工作区的src目录的导入路径来引用你的自定义包。
```
package main

import (
    "myproject/mypackage"
)

func main() {
    mypackage.MyFunction()
}
```

在新版本的Go中，你还可以使用Go模块来管理你的代码和依赖。  
这样，你就可以在工作区之外创建项目，并不再需要设置GOPATH。  
只需在项目根目录下运行go mod init myproject来初始化一个新的模块。


## 更改工作区
如果你对工作区进行了任何更改（如删除或移动 go.mod 文件），请重新启动 gopls。  
如果你使用的是 VS Code，可以执行 "Go: Restart Language Server" 命令



# 包、变量、函数

## 导入自定义包
improt (
    "项目路径/包目录"
)
项目路径是go.mod所在的目录
包目录是自定义包文件所在的目录
## 导出名
名字以大写字母开头是已导出的（包外可用）
未导出名包外不可用


## 函数
函数连续两个及以上命名形参相同，可以只写最后一个的类型
### 函数可返回任意数量的返回值
### 命名返回值
Go的返回值可以被命名，它们会被看作定义在函数顶部的变量
没有参数的return语句返回已命名的返回值（直接返回）
直接返回语句应该仅用在段函数中。（长函数中影响可读性）
```
func split(sum int) (x, y int) {
    x = sum*4/9
    y = sum-x
    return // 直接返回
}
```

## 变量
var语句用于声明变量列表，类型名在最后
```
var c, python, java bool
```
**声明变量不指定类型时发生类型推导，从右值推导**  

变量声明可包含初始值，每个变量对应一个。有初始值可以省略类型，从初始值自动获得类型
```
var c, python, java = true, false, "no!"
```

简短变量声明只能用于函数内
```
x := 2  // 错误：函数体外的非声明语句
func main() {
	var i, j int = 1, 2 // 普通赋值
	k := 3              // 简短变量声明
	c, python, java := true, false, "no!"   // 简短变量声明

	fmt.Println(i, j, k, c, python, java)
}
```

### 零值
没有明确初始值的变量声明会赋 零值
数值类型为0，布尔类型false，字符串为""

### 类型转换 T(v)


### 常量
常量使用const关键字。不能使用:=语法
const World = "世界"



## 赋值 := 和 =
:= 简短变量声明 （可不指定类型名，go自动推断类型）
* := 是一个声明并初始化变量的快捷方式。
* 使用 := 可以在不指定变量类型的情况下声明变量，并立即为其赋值。Go 会自动根据右侧的值推断变量类型。
* := 只能在函数体内使用。

= 赋值操作符
* = 是一个简单的赋值操作符，用于将一个值赋给已声明的变量。
* 使用 = 之前，变量必须已经被声明。
* 可以在任何作用域内使用。


# 流程控制语句
for、if、else、switch、defer

# 更多类型：struct、slice、映射、函数闭包


# 方法和接口
## 方法
go没有类。但可以给结构体类型定义方法。方法是有特殊的**接收者参数**的函数
方法接收者在自己的参数列表内，位于func关键字和方法名之间
```
type Vertex struct {    // 结构体
	X, Y float64
}

// 方法的接收者参数，在func关键字和方法名之间。本例接收者参数即Vertex结构体v
func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}
```

## 接口
接口类型 - 一组方法签名定义的集合
接口类型变量可以保存任何实现了这些方法的值