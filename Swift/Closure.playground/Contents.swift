//: Playground - noun: a place where people can play

import UIKit

var arr:[Int] = [ 1,3,5,6,7,2,4,6,8,0]
arr = arr.sort({(a:Int,b:Int)->Bool in
        return a>b
})
arr

arr = [ 1,3,5,6,7,2,4,6,8,0]
arr = arr.sort({(a:Int,b:Int)->Bool in return a>b})
arr

arr = [ 1,3,5,6,7,2,4,6,8,0]
arr = arr.sort({a,b in return a>b})
arr

arr = [ 1,3,5,6,7,2,4,6,8,0]
arr = arr.sort({a,b in a>b})
arr

arr = [ 1,3,5,6,7,2,4,6,8,0]
arr = arr.sort({$0>$1})
arr

arr = [ 1,3,5,6,7,2,4,6,8,0]
arr = arr.sort(>)
arr