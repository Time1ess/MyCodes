//
//  ViewController.swift
//  ChineseZodiac
//
//  Created by 杜佑宸 on 16/1/22.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var yearOfBirth: UITextField!
    
    @IBOutlet weak var image: UIImageView!
    
    let OFFSET=4
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        yearOfBirth.becomeFirstResponder()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func touchesEnded(touches: Set<UITouch>, withEvent event: UIEvent?) {
        yearOfBirth.resignFirstResponder()
    }
    
    @IBAction func OkDetected(sender: AnyObject) {
        yearOfBirth.resignFirstResponder()
        var year:Int = 1993
        if !yearOfBirth.text!.isEmpty
        {
            year = Int(yearOfBirth.text!)!
            year = year>0 ? year : 0
            let imageNumber = year>3 ? ((year-OFFSET)%12) : year
            image.image = UIImage(named: String(imageNumber))
        }
    }
    
    
}

