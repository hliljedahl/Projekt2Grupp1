//
//  FirstViewController.swift
//  SmartSystem0.3
//
//  Created by Hampus Liljedahl on 2018-04-17.
//  Copyright © 2018 LiljedahlLabs. All rights reserved.
//

import UIKit
import Charts



struct Inst: Decodable {
	let updte: String
	let max: String
	let plchldr: String
	let id: String
}

var instVal = [Inst]()
var instMax = [String]()
var updtInt = 0
var instInt = 0
var instType = 0
var updtString = ""
var instString = ""
var val = 0

class FirstViewController: UIViewController {
	
	
	var dropUpd: UIDropDown!
	var dropInt: UIDropDown!
	
	@IBOutlet weak var labelUpd: UILabel!
	@IBOutlet weak var labelInt: UILabel!
	@IBOutlet weak var webView: UIWebView!
	@IBOutlet weak var webView2: UIWebView!
	
		@IBAction func currentBut(_ sender: Any){
		updateInst()
		updateSensor()
		var maxMin = 0
		switch instVal[0].updte {
			case "1":
				self.labelInt.text = "Update interval: 1 min"
				maxMin = 1
			case "2":
				self.labelInt.text = "Update interval: 10 min"
				maxMin = 10
			case "3":
				self.labelInt.text = "Update interval: 30 min"
				maxMin = 30
			case "4":
				self.labelInt.text = "Update interval: 1 hour"
				maxMin = 60
			case "5":
				self.labelInt.text = "Update interval: 2 hours"
				maxMin = 120
			case "6":
				self.labelInt.text = "Update interval: 3 hours"
				maxMin = 180
			case "7":
				self.labelInt.text = "Update interval: 6 hours"
				maxMin = 360
			case "8":
				self.labelInt.text = "Update interval: 12 hours"
				maxMin = 720
			case "9":
				self.labelInt.text = "Update interval: 24 hours"
				maxMin = 1440
			default:
				print ("no value")
		}
		let maxIn = (Int(instVal[0].updte)!/Int(sensVal.count))*maxMin
		
		switch maxIn {
		case 1440:
			self.labelUpd.text = "Time interval: 1 day"
		case 2880:
			self.labelUpd.text = "Time interval: 2 days"
		case 10080:
			self.labelUpd.text = "Time interval: 1 week"
		case 20160:
			self.labelUpd.text = "Time interval: 2 weeks"
		case 40320:
			self.labelUpd.text = "Time interval: 4 weeks"
		case 80640:
			self.labelUpd.text = "Time interval: 8 weeks"
		default:
			print ("no value")
		}
		
		
	}
	@IBAction func updateBut(_ sender: Any) {
		updateInst()
		updateSensor()
		
		let preweburl = "http://www.lonelycircuits.se/data/add_inst.php?"
		let ubdt = "update=%22"
		let inst = "max=%22"
		let app = "%22"
		var weburl = ""
		var weburl2 = ""
		var minutes = 0
		let nrOfSens = sensVal.count
		
		print(instMax)
		print(instVal[0].updte)
		
		switch instInt {
			case 0:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 1
			case 1:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 10
				//print("Number is 150")
			case 2:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 30
				//print("Number is 150")
			case 3:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 60
				//print("Number is 150")
			case 4:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 120
				//print("Number is 150")
			case 5:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 180
				//print("Number is 150")
			case 6:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 360
				//print("Number is 150")
			case 7:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 720
			case 8:
				weburl = preweburl + ubdt + String(instInt+1) + app
				minutes = 1440
				//print("Number is 150")

			default:
				//weburl = preweburl + ubdt + String(1) + app
				//minutes = 1
				print ("no value")
			}
		//print(instVal)
		//let weburl = preweburl + ubdt + String(val) + app
		let url = (URL(string: weburl))
		self.webView.loadRequest(URLRequest(url: url!))
		
		
		switch updtInt {
		case 0:
			let values = ((24*60)/minutes)*nrOfSens
			weburl2 = preweburl + inst + String(values) + app
			
		case 1:
			let values = ((48*60)/minutes)*nrOfSens
			weburl2 = preweburl + inst + String(values) + app
		//print("Number is 150")
		case 2:
			let values = ((168*60)/minutes)*nrOfSens
			weburl2 = preweburl + inst + String(values) + app
		//print("Number is 150")
		case 3:
			let values = ((336*60)/minutes)*nrOfSens
			weburl2 = preweburl + inst + String(values) + app
		//print("Number is 150")
		case 4:
			let values = ((672*60)/minutes)*nrOfSens
			weburl2 = preweburl + inst + String(values) + app
		//print("Number is 150")
		case 5:
			let values = ((1344*60)/minutes)*nrOfSens
			weburl2 = preweburl + inst + String(values) + app
		//print("Number is 150")
		default:
			print("Otherwise, do something else.")
		}
		
		//print(instVal)
		//let weburl = preweburl + ubdt + String(val) + app
		let url2 = (URL(string: weburl2))
		self.webView2.loadRequest(URLRequest(url: url2!))
		
	}
	
	@IBOutlet var Names: [UIButton]!
	override func viewDidLoad() {
		super.viewDidLoad()
		updateData()
		updateInst()
		updateSensor()
		updateZones()
		updateInst()
		
		print(instMax)
		

		dropUpd = UIDropDown(frame: CGRect(x: 300, y: 200, width: 300, height: 30))
		dropUpd.center = CGPoint(x: 585, y: 820)
		dropUpd.placeholder = "Select your time interval..."
		dropUpd.options = ["1 day", "2 days", "1 week", "2 weeks", "4 weeks","8 weeks"]
		dropUpd.didSelect { (option, index) in
			self.labelUpd.text = "Time interval: \(option)"
			//zoneID = Int(zoneVal[index].id)!
			//self.updateGraph()
			updateInst()
			//print(instVal)
			//var val = 0
			updtInt = index
			
			print("You just select: \(option) at index: \(index)")
		}
		self.view.addSubview(dropUpd)
		
		dropInt = UIDropDown(frame: CGRect(x: 300, y: 200, width: 300, height: 30))
		dropInt.center = CGPoint(x: 175, y: 820)
		dropInt.placeholder = "Select your update interval..."
		dropInt.options = ["1 min", "10 min", "30 min", "1 hour", "2 hours", "3 hours", "6 hours", "12 hours", "24 hours"]
		dropInt.didSelect { (option, index) in
			self.labelInt.text = "Update interval: \(option)"

			updateInst()
			instInt = index
			
			print("You just select: \(option) at index: \(index)")
		}
		self.view.addSubview(dropInt)
		
		
		
		// Do any additional setup after loading the view, typically from a nib.
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		updateInst()
		// Dispose of any resources that can be recreated.
	}
	
	@IBAction func HandleAboutUs(_ sender: UIButton) {
		updateInst()
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
		updateInst()
		Names.forEach{ (button) in
			button.isHidden = !button.isHidden
			
			guard let title = sender.currentTitle, let _ = NAMES(rawValue: title) else {
				
				return
			}
		}
	}


}

