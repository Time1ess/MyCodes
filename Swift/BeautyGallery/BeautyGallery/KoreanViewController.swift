//
//  KoreanViewController.swift
//  BeautyGallery
//
//  Created by 杜佑宸 on 16/1/25.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import UIKit
import Social

class KoreanViewController: UIViewController {
    
    @IBOutlet weak var beautyImage: UIImageView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func FacebookClicked(sender: AnyObject) {
        let controller:SLComposeViewController =
        SLComposeViewController(forServiceType: SLServiceTypeFacebook)
        
        controller.setInitialText("Social Framework初始化文字测试!")
        controller.addImage(beautyImage.image)
        
        self.presentViewController(controller, animated: true, completion: nil)
    }
    
    @IBAction func TwitterClicked(sender: AnyObject) {
        let controller:SLComposeViewController =
        SLComposeViewController(forServiceType: SLServiceTypeTwitter)
        
        controller.setInitialText("Social Framework初始化文字测试!")
        controller.addImage(beautyImage.image)
        
        self.presentViewController(controller, animated: true, completion: nil)
    }
    
    @IBAction func WeiboClicked(sender: AnyObject) {
        let controller:SLComposeViewController =
        SLComposeViewController(forServiceType: SLServiceTypeSinaWeibo)
        
        controller.setInitialText("Social Framework初始化文字测试!")
        controller.addImage(beautyImage.image)
        
        self.presentViewController(controller, animated: true, completion: nil)
    }
}
