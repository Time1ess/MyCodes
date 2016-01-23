//
//  ViewController.swift
//  LoveFinder
//
//  Created by 杜佑宸 on 16/1/23.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import UIKit

class ViewController: UIViewController,UITextFieldDelegate {

    @IBOutlet weak var name: UITextField!
    @IBOutlet weak var gender: UISegmentedControl!
    @IBOutlet weak var birth: UIDatePicker!
    @IBOutlet weak var heightNumber: UISlider!
    @IBOutlet weak var height: UILabel!
    @IBOutlet weak var house: UISwitch!
    @IBOutlet weak var result: UITextView!
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        name.delegate = self
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func HeightChanged(sender: AnyObject) {
        let slider = sender as! UISlider
        height.text = "\(Int(slider.value))厘米"
    }

    @IBAction func OkDetected(sender: AnyObject) {
        let genderText = gender.selectedSegmentIndex == 0 ? "高富帅" : "白富美"
        let gregorian = NSCalendar(calendarIdentifier:NSCalendarIdentifierGregorian)
        
        let now = NSDate()
        
        let components = gregorian?.components(NSCalendarUnit.NSYearCalendarUnit, fromDate: birth.date, toDate: now, options: NSCalendarOptions(rawValue: 0))
        let age = components!.year
        
        let hasHouse = house.on ? "有房" : "无房"
        result.text = "\(name.text!),\(genderText),\(age)岁,身高\(height.text!),\(hasHouse)，求交往！"
    }
    
    //UITextFieldDelegate
    
    func textFieldShouldReturn(textField: UITextField) -> Bool
    {
        textField.resignFirstResponder()
        return true
    }
}

