//
//  Unsplasher.swift
//  Unsplash
//
//  Created by 杜佑宸 on 2016/10/11.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import Cocoa
import Alamofire

class Unsplasher: NSObject {
    
    
    static let high_resolution = "2880x1800"
    static let low_resolution = "1920x1080"
    static let img_url = "https://source.unsplash.com"
    static let categories = ["建筑": "buildings", "食物": "food", "自然": "nature",
                      "人物": "people", "科技": "technology", "物体": "objects"]
    static let hour_per_day = 24
    static let hour_per_week = hour_per_day*7
    static let invervals = ["每10分钟": 10, "每30分钟": 30, "每1小时": 120,
                                  "每2小时": 120, "每5小时": 300,
                                  "每天": 60*hour_per_day,
                                  "每周": 60*hour_per_week]
    static let resolutions = ["高分辨率(2880*1800)": high_resolution,
                              "低分辨率(1920*1080)": low_resolution]
    static var _cates : [String] = []
    static var _interval: Int = 10
    static var _resolution: String = high_resolution
    static var _timestamp: Int = 0

    static func gen_api_url() -> String
    {
        if _cates.count == 0
        {
            return img_url+"/random/"+_resolution
        }
        else
        {
            let randomIndex = Int(arc4random_uniform(UInt32(_cates.count)))
            return img_url+"/category/"+_cates[randomIndex]+"/"+_resolution
        }
    }
    
    static func set_background(file_path : URL)
    {
        do {
            let ws = NSWorkspace.shared()
            for screen in NSScreen.screens()!
            {
                let opts = ws.desktopImageOptions(for: screen)
                try ws.setDesktopImageURL(file_path, for: screen, options: opts!)
            }
        } catch {
        }
    }
    
    static func download_background(url : String, recursive: Bool)
    {
        let destination = DownloadRequest.suggestedDownloadDestination(for: .cachesDirectory)
        Alamofire.download(url, to: destination).response { response in
            if(response.error == nil)
            {
                set_background(file_path: response.destinationURL!)
                if(recursive == true)
                {
                    let now = NSDate()
                    let time_interval:TimeInterval = now.timeIntervalSince1970
                    _timestamp = Int(time_interval)+_interval*60
                    StatusMenuController.update_label_time(timestamp: _timestamp)
                    DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(Unsplasher._interval*60), execute: {
                        Unsplasher.update_background(recursive: true)
                    })
                }
            }
        }
    }

    static func update_background(recursive: Bool = true)
    {
        let url = gen_api_url()
        download_background(url : url, recursive : recursive)
    }
    
    func receiveWakeNote(note: NSNotification)
    {
        let now = NSDate()
        let time_interval:TimeInterval = now.timeIntervalSince1970
        let timestamp = Int(time_interval)
        if(timestamp > Unsplasher._timestamp)
        {
            print("Too late, Update now!")
            Unsplasher._timestamp = timestamp+Unsplasher._interval*60
            StatusMenuController.update_label_time(timestamp: Unsplasher._timestamp)
            DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(Unsplasher._interval*60), execute: {
                Unsplasher.update_background(recursive: true)
            })
        }
        else
        {
            print("It's not too late, waiting...")
        }
    }

    override func awakeFromNib() {
        Unsplasher.update_background()
        NSWorkspace.shared().notificationCenter.addObserver(
            self, selector: #selector(Unsplasher.receiveWakeNote),
            name: NSNotification.Name.NSWorkspaceDidWake, object: nil)
    }
    
    static func update_available_category(cate_chn : String)
    {
        if let cate = categories[cate_chn] {
            if let index = _cates.index(of: cate)
            {
                _cates.remove(at: index)
            }
            else
            {
                _cates.append(cate)
            }
        }
    }
    
    static func update_interval(interval_chn : String)
    {
        if let interval = invervals[interval_chn] {
            _interval = interval
        }
    }
    
    static func update_resolution(resolution_chn : String)
    {
        if let resolution = resolutions[resolution_chn] {
            _resolution = resolution
        }
    }
    

}
