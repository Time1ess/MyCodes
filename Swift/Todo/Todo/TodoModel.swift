//
//  TodoModel.swift
//  Todo
//
//  Created by 杜佑宸 on 16/1/26.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import UIKit

class TodoModel: NSObject {
    var id: String
    var image: String
    var title: String
    var date: NSDate
    
    init(id: String, image: String, title: String, date: NSDate)
    {
        self.id = id
        self.image = image
        self.title = title
        self.date = date
    }
}
