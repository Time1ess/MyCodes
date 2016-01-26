//
//  ViewController.swift
//  Todo
//
//  Created by 杜佑宸 on 16/1/26.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//

import UIKit

var todos: [TodoModel] = []

func DateFromString(dateStr: String) -> NSDate?
{
    let dateFormatter = NSDateFormatter()
    dateFormatter.dateFormat = "YYYY-MM-dd"
    let date = dateFormatter.dateFromString(dateStr)
    return date
}

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate{
    
    @IBOutlet weak var tableView: UITableView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        todos = [
            TodoModel(id: "1", image: "child-selected", title: "1. 去游乐场",
                date: DateFromString("2016-01-01")!),
            TodoModel(id: "2", image: "shopping-cart-selected", title: "2. 购物",
                date: DateFromString("2016-01-03")!),
            TodoModel(id: "3", image: "phone-selected", title: "3. 打电话",
                date: DateFromString("2016-01-04")!),
            TodoModel(id: "4", image: "travel-selected", title: "4. 去欧洲",
                date: DateFromString("2016-01-07")!)]
        
        navigationItem.leftBarButtonItem = editButtonItem()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    // Protocol UITableViewDataSource
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int
    {
        return todos.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell
    {
        let cell=self.tableView.dequeueReusableCellWithIdentifier("todoCell")! as UITableViewCell
        let todo = todos[indexPath.row] as TodoModel
        
        let image = cell.viewWithTag(101) as! UIImageView
        let title = cell.viewWithTag(102) as! UILabel
        let date = cell.viewWithTag(103) as! UILabel
        
        image.image = UIImage(named: todo.image)
        title.text = todo.title
        
        let locale = NSLocale.currentLocale()
        let dateFormat = NSDateFormatter.dateFormatFromTemplate("YYYY-MM-dd",
            options: 0, locale: locale)
        let dateFormatter = NSDateFormatter()
        dateFormatter.dateFormat = dateFormat
        
        date.text = dateFormatter.stringFromDate(todo.date)
        return cell
    }
    
    // Protocol UITableViewDelegate
    func tableView(tableView: UITableView, commitEditingStyle editingStyle: UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath)
    {
        if editingStyle == UITableViewCellEditingStyle.Delete
        {
            todos.removeAtIndex(indexPath.row)
            self.tableView.deleteRowsAtIndexPaths([indexPath], withRowAnimation: UITableViewRowAnimation.Automatic)
        }
    }
    
    override func setEditing(editing: Bool, animated: Bool) {
        super.setEditing(editing, animated: animated)
        self.tableView.setEditing(editing, animated: animated)
    }
}

