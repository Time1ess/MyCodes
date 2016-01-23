//: Playground - noun: a place where people can play

import UIKit

let colors =
[
    "Air Force Blue":(red:93,green:138,blue:168),
    "Bittersweet":(red:254,green:111,blue:94),
    "Canary Yellow":(red:255,green:239,blue:0),
    "Dark Orange":(red:255,green:140,blue:0),
    "Electric Violet":(red:143,green:0,blue:255),
    "Fern":(red:113,green:188,blue:120),
    "Gamboge":(red:228,green:155,blue:15),
    "Hollywood Cerise":(red:244,green:0,blue:161),
    "Icterine":(red:252,green:247,blue:94),
    "Jazzberry Jam":(red:165,green:11,blue:94)
]

var back_view = UIView(frame: CGRectMake(0.0,0.0,320.0,
    CGFloat(colors.count * 50)))

back_view.backgroundColor = UIColor.blackColor()

back_view
var index = 0
for (color_name,rgb_tuple) in colors
{
    var color_stripe = UILabel(frame: CGRectMake(0.0,CGFloat(index * 50 + 5),
        320.0,40.0))
    color_stripe.backgroundColor = UIColor(red: CGFloat(rgb_tuple.red) / 255.0,
        green: CGFloat(rgb_tuple.green) / 255.0,
        blue: CGFloat(rgb_tuple.blue) / 255.0,
        alpha: 1.0)
    color_stripe
    
    var color_name_label = UILabel(frame: CGRectMake(0.0,0.0,300.0,40.0))
    color_name_label.font = UIFont(name:"Arial", size:24.0)
    color_name_label.textColor = UIColor.blackColor()
    color_name_label.textAlignment = NSTextAlignment.Right
    color_name_label.text = color_name
    
    color_stripe.addSubview(color_name_label)
    
    back_view.addSubview(color_stripe)
    index++
}
back_view