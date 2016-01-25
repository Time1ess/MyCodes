import Foundation
var str="hello,playground"
str.capitalizedString
str
str.uppercaseString
str.lowercaseString


var str2="   !!ad!f!!i!!!!    "
str2.stringByTrimmingCharactersInSet(NSCharacterSet.whitespaceCharacterSet())
str2
str2.stringByTrimmingCharactersInSet(NSCharacterSet(charactersInString: " !"))

var str3="welcome to swift playground"
str3.componentsSeparatedByString(" ")
var array = ["A","B","C","D","E","F"]
array.count
array.isEmpty
array.insert("HELLO", atIndex: 0)
array[0...2]=[]
array
array[0...1]=["1","2","3","4"]
array

for (index,item) in array.enumerate()
{
    print("\(index)-\(item)")
}

var tuple = (name:"david",age:18,gender:"male")
tuple
tuple.name
tuple.0

var dictionary = [1:"A",2:"B",3:"C"]
dictionary[2]
dictionary[6]="COLE"
dictionary
var dictionary2 = Dictionary<Int,String>()
var dictionary3 = [String:String]()
var dictionary4 :Dictionary<String,String> = ["name":"david","age":"18","gender":"male"]

dictionary4.count

dictionary4.isEmpty
"my age is" + dictionary4["age"]!
print(dictionary4["age"])
dictionary4["home"]
var old_value = dictionary4.updateValue("youchen", forKey: "name")
dictionary4
old_value

var old_value2 = dictionary4.removeValueForKey("gender")

dictionary4["gender"] = "male"
dictionary4["school"] = "DLUT"

for (key,value) in dictionary4
{
    print(key,value)
}

dictionary4.keys
dictionary4.values

for key in dictionary4.keys
{
    print(key)
}

for value in dictionary4.values
{
    print(value)
}

Array(dictionary4.keys)

let mydict = ["libingbing":"李冰冰","fanbingbing":"范冰冰"]
print(mydict["libingbing"])
print(mydict["yangmi"])
