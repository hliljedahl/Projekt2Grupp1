//
//  FirstViewController.swift
//  SmartSystem0.3
//
//  Created by Hampus Liljedahl on 2018-04-17.
//  Copyright © 2018 LiljedahlLabs. All rights reserved.
//

import UIKit
import Charts

class FirstViewController: UIViewController {
	
	
	var dropUpd: UIDropDown!
	var dropInt: UIDropDown!
	
	@IBOutlet weak var labelUpd: UILabel!
	@IBOutlet weak var labelInt: UILabel!
	@IBOutlet weak var webView: UIWebView!
	
	@IBOutlet var Names: [UIButton]!
	override func viewDidLoad() {
		super.viewDidLoad()
		updateData()
		updateSensor()
		updateZones()
		let preweburl = "http://www.lonelycircuits.se/data/add_inst.php?" //update=%222%22"
		let ubdt = "update=%22"
		let app = "%22"
		dropUpd = UIDropDown(frame: CGRect(x: 300, y: 200, width: 300, height: 30))
		dropUpd.center = CGPoint(x: 595, y: 200)
		dropUpd.placeholder = "Select your time intervall..."
		dropUpd.options = ["12 hours","1 day", "2 days", "1 week", "2 weeks", "4 weeks","8 weeks"]
		dropUpd.didSelect { (option, index) in
			self.labelUpd.text = "Update intervall: \(option)"
			//zoneID = Int(zoneVal[index].id)!
			//self.updateGraph()
			
			let val = String(index + 1)
			let weburl = preweburl + ubdt + val + app
			let url = (URL(string: weburl))
			self.webView.loadRequest(URLRequest(url: url!))
			
			print("You just select: \(option) at index: \(index)")
		}
		self.view.addSubview(dropUpd)
		
		dropInt = UIDropDown(frame: CGRect(x: 300, y: 200, width: 300, height: 30))
		dropInt.center = CGPoint(x: 175, y: 200)
		dropInt.placeholder = "Select your update intervall..."
		dropInt.options = ["1 min", "10 min", "30 min", "1 hour", "3 hours", "6 hours", "12 hours", "24 hours"]
		dropInt.didSelect { (option, index) in
			self.labelInt.text = "Time intervall: \(option)"
			//zoneID = Int(zoneVal[index].id)!
			//self.updateGraph()
			
			let val = String(index + 1)
			let weburl = preweburl + ubdt + val + app
			let url = (URL(string: weburl))
			self.webView.loadRequest(URLRequest(url: url!))
			
			print("You just select: \(option) at index: \(index)")
			print("You just select: \(option) at index: \(index)")
		}
		self.view.addSubview(dropInt)
		
		
		
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


}

