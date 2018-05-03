//
//  FirstViewController.swift
//  prijekttest
//
//  Created by Linnea Björck on 2018-04-18.
//  Copyright © 2018 Linnea Björck. All rights reserved.
//

import UIKit

class FirstViewController: UIViewController {

    @IBOutlet var Names: [UIButton]!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func HandleAboutUs(_ sender: UIButton) {
     
            Names.forEach{ (button) in
            UIView.animate(withDuration: 0.3, animations:{
                button.isHidden = !button.isHidden
                self.view.layoutIfNeeded()
                
            })
        }
    
    }
    enum NAMES: String {
        case arvid = "Arvid"
        case hampus = "Hampus"
        case johan = "Johan"
        case linnea = "Linnea"
        
    }
    
    @IBAction func nameTapped(_ sender: UIButton) {
        
        Names.forEach{ (button) in
        button.isHidden = !button.isHidden
            
            guard let title = sender.currentTitle, let _ = NAMES(rawValue: title) else {
          
            return
            }
        }
    }
        
   //     switch names {
    //    case .arvid:
       //     print ("African American Fellow")
     //   default:
        //    print ("Någon annan")
       // }
        
   // }
    
    
}

