//
//  ViewController.swift
//  CALayer
//
//  Created by 杜佑宸 on 16/1/28.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import UIKit

class ViewController: UIViewController {


    @IBOutlet weak var viewForLayer: UIView!

    let layer = CALayer()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        SetUpLayer()
        viewForLayer.layer.addSublayer(layer)
    }
    
    func SetUpLayer()
    {
        // 1
        layer.frame = viewForLayer.bounds

        // 2
        layer.contents = UIImage(named: "star")?.CGImage
        layer.contentsGravity = kCAGravityCenter

        // 3
        layer.magnificationFilter = kCAFilterLinear
        layer.geometryFlipped = false

        // 4
        layer.backgroundColor = UIColor(red: 11/255.0, green: 86/255.0, blue: 14/255.0, alpha: 1.0).CGColor
        layer.opacity = 1.0
        layer.hidden = false
        layer.masksToBounds = false
      
        // 5
        layer.cornerRadius = 150.0
        layer.borderWidth = 12.0
        layer.borderColor = UIColor.whiteColor().CGColor

        // 6
        layer.shadowOpacity = 0.75
        layer.shadowOffset = CGSize(width: 0, height: 3)
        layer.shadowRadius = 3.0


    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

