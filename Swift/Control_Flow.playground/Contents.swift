//: Playground - noun: a place where people can play

import UIKit

for i in -99...99
{
    i * i
}

let str = "Hello,world"

for ch in str.characters
{
    print(ch)
}

let list = ["david","male","dlut"]

for (index,item) in list.enumerate()
{
    print(index,item)
}

let dict = [1:"david",5:"male","7":"dlut"]

for (key,value) in dict
{
    print(key,value)
}

let base = 2
let power = 10
var result = 1

for _ in 1...power
{
    result *= base;
}
result

for var i = -6.28;i<=6.28;i+=0.1
{
    sin(i)
}


//binary_search

//var datas : [Int] = []
//for var i = 0 ; i < 100 ; i++
//{
//    datas.append(Int(arc4random()%1000))
//}
//datas = datas.sort(<)
//datas
//
//var min = 0, max = datas.count
//var target = Int(arc4random()%1000)
//var mid : Int
//while min < max
//{
//    mid = (min+max)/2
//    datas[mid]
//    if datas[mid]==target
//    {
//        print("\(target) is found in index \(mid)")
//        break
//    }
//    else if datas[mid]<target
//    {
//        min = mid+1
//    }
//    else
//    {
//        max = mid-1
//    }
//}
//if min>=max
//{
//    print("\(target) not found.")
//}

var rating = "a"

switch rating
{
    case "A","a":
    print("Great!")
    case "B":
    print("Just so-so.")
default:
    print("It's Bad.")
}

var score = 101

switch score
{
case 0:
    print("You got an egg!")
case 1..<60:
    print("Sorry,you failed.")
case 60:
    print("Just passed.")
case 61..<70:
    print("Just so-so.")
case 70..<80:
    print("Not bad")
case 80..<90:
    print("Good job!")
case 90..<100:
    print("Great!")
case 100:
    print("Perfect!")
default:
    print("Something wrong with your score")
}

var coordinate = (1,1)

switch coordinate
{
case (0,0):
    print("here")
case (1,1):
    print("there")
default:
    print("where?")
}

var coordinate2 = (3,5)

switch coordinate2
{
case (0,0):
    print("here")
case (_,0):
    print("x_axis")
case (0,_):
    print("y_axis")
case (-3...3,3):
    print("near y=3")
case (let x,5):
    print("\(x)")
default:
    print("where?")
}

//where
let coordinate3 = (3,3)
switch coordinate3
{
case let (x,y) where x == y:
    print("x==y")
case let(x,y) where x == -y:
    print("x==-y")
case let (x,y):
    print("some arbitrary point")
}

let coord = (5,0)
switch coord
{
case (0,0):
    print("origin")
    fallthrough
case (_,0):
    print("x_axis")
    fallthrough
case (0,_):
    print("y_axis")
    fallthrough
default:
    print("point")
}
