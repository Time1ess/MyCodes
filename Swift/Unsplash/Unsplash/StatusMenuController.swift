//
//  StatusMenuController.swift
//  Unsplash
//
//  Created by 杜佑宸 on 2016/10/11.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import Cocoa

class StatusMenuController: NSObject {
    @IBOutlet weak var statusMenu: NSMenu!
    @IBOutlet weak var label_next_update: NSMenuItem!
    @IBOutlet weak var about_window: NSWindow!
    
    static var date_label: NSMenuItem?
    
    let statusItem = NSStatusBar.system().statusItem(withLength: NSVariableStatusItemLength)
    
    
    @IBOutlet weak var current_interval: NSMenuItem!
    @IBOutlet weak var current_resolution: NSMenuItem!
    
    override func awakeFromNib() {
        let img = NSImage(named: "status_icon")
        statusItem.image = img
        statusItem.menu = statusMenu
        StatusMenuController.date_label = label_next_update
    }
    
    static func flush_update()
    {
        
    }
    
    static func update_label_time(timestamp : Int)
    {
        let dformatter = DateFormatter()
        dformatter.dateFormat = "MM/dd HH:mm"
        let date = Date(timeIntervalSince1970: TimeInterval(timestamp))
        let time_str = dformatter.string(from: date)
        StatusMenuController.date_label?.title = "下次更新:"+time_str
    }

    @IBAction func aboutClicked(_ sender: AnyObject) {
        about_window.makeKeyAndOrderFront(nil)
    }
    
    @IBAction func quitClicked(sender: NSMenuItem) {
        NSApplication.shared().terminate(self)
    }
    
    @IBAction func update_background_now(_ sender: AnyObject) {
        Unsplasher.update_background(recursive: false)
    }
    
    @IBAction func set_category(_ sender: AnyObject) {
        let item = sender as! NSMenuItem
        let title = item.title
        item.state = NSOnState + NSOffState - item.state
        Unsplasher.update_available_category(cate_chn: title)
    }
    
    @IBAction func set_interval(_ sender: AnyObject) {
        let item = sender as! NSMenuItem
        if(item == current_interval)
        {
            return
        }
        current_interval?.state = NSOffState
        item.state = NSOnState
        current_interval = item
        let title = item.title
        Unsplasher.update_interval(interval_chn: title)
    }
    
    @IBAction func set_resolution(_ sender: AnyObject) {
        let item = sender as! NSMenuItem
        if(item == current_resolution)
        {
            return
        }
        current_resolution?.state = NSOffState
        item.state = NSOnState
        current_resolution = item
        let title = item.title
        Unsplasher.update_resolution(resolution_chn: title)
    }
    
}
