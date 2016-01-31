//
//  DetailViewController.swift
//  Todo
//
//  Created by 杜佑宸 on 16/1/27.
//  Copyright © 2016年 杜佑宸. All rights reserved.
//
import UIKit

class DetailViewController: UIViewController, UITextFieldDelegate {
    
    @IBOutlet weak var childButton: UIButton!
    @IBOutlet weak var phoneButton: UIButton!
    @IBOutlet weak var shoppingCartButton: UIButton!
    @IBOutlet weak var planeButton: UIButton!
    @IBOutlet weak var todoItem: UITextField!
    @IBOutlet weak var todoDate: UIDatePicker!
    
    var todo: TodoModel?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        todoItem.delegate = self
        
        if todo != nil
        {
            navigationController?.title = "修改"
            switch todo!.image
            {
            case "child-selected":
                childButton.selected = true
            case "phone-selected":
                phoneButton.selected = true
            case "shopping-cart-selected":
                shoppingCartButton.selected = true
            case "travel-selected":
                planeButton.selected = true
            default:
                break
            }
            
            todoItem.text = todo!.title
            todoDate.date = todo!.date
        }
        else
        {
            childButton.selected = true
            navigationController?.title = "新增"
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
        
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool
    {
        textField.resignFirstResponder()
        return true
    }
    
    override func touchesEnded(touches: Set<UITouch>, withEvent event: UIEvent?) {
        todoItem.resignFirstResponder()
    }
    
    func ResetButtons()
    {
        childButton.selected = false
        phoneButton.selected = false
        shoppingCartButton.selected = false
        planeButton.selected = false
        
    }
    
    @IBAction func ChildTapped(sender: AnyObject) {
        ResetButtons()
        childButton.selected = true
    }
    
    @IBAction func PhoneTapped(sender: AnyObject) {
        ResetButtons()
        phoneButton.selected = true
    }
    
    @IBAction func ShoppingCartTapped(sender: AnyObject) {
        ResetButtons()
        shoppingCartButton.selected = true
    }
    
    @IBAction func PlaneTapped(sender: AnyObject) {
        ResetButtons()
        planeButton.selected = true
    }
    
    @IBAction func OkTapped(sender: AnyObject) {
        var image = ""
        if childButton.selected
        {
            image = "child-selected"
        }
        else if phoneButton.selected
        {
            image = "phone-selected"
        }
        else if shoppingCartButton.selected
        {
            image = "shopping-cart-selected"
        }
            
        else if planeButton.selected
        {
            image = "travel-selected"
        }
        if todo == nil
        {
            let uuid = NSUUID().UUIDString
            todo = TodoModel(id: uuid, image: image, title: todoItem.text!, date: todoDate.date)
            todos.append(todo!)
        }
        else
        {
            todo!.image = image
            todo!.title = todoItem.text!
            todo!.date = todoDate.date
        }
        
    }
}
