//: Playground - noun: a place where people can play

import UIKit

enum GameEnding{
    case Win
    case Lose
    case Draw
}

var yourScore:Int = 80
var enemyScore:Int = 90

var theGameEnding:GameEnding

if yourScore > enemyScore
{
    theGameEnding = GameEnding.Win
}
else if yourScore == enemyScore
{
    theGameEnding = .Draw
}
else
{
    theGameEnding = .Lose
}

switch theGameEnding
{
case .Win:
    print("You win")
case .Lose:
    print("You lose")
case .Draw:
    print("It's a draw")
}

enum Barcode{
    case UPCA(Int,Int,Int,Int)
    case QRCode(String)
}

let productCodeA = Barcode.UPCA(4, 102, 345, 8)
let productCodeB:Barcode = .QRCode("This is an information")

switch productCodeA
{
case .UPCA(let numberSystem,let manufacturer,let identifier,let check):
    print("UPC-A with value of \(numberSystem),\(manufacturer),\(identifier),\(check)")
case .QRCode(let productCode):
    print("QR code with value of \(productCode).")
}