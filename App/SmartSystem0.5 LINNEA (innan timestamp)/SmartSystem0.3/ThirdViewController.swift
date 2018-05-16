//
//  FirstViewController.swift
//  SmartSystem0.3
//
//  Created by Hampus Liljedahl on 2018-04-17.
//  Copyright © 2018 LiljedahlLabs. All rights reserved.
//

import UIKit
import Charts
import Foundation

class ThirdViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
	
	@IBOutlet weak var tableView1: UITableView!
	@IBOutlet weak var tableView2: UITableView!
	@IBOutlet weak var webView3: UIWebView!
	
	var zoneIndex = 0
	var select = 0
	var sensArray = [String]()
	var newZone = ""
	
	func refresh(){
		
		updateSensor()
		updateZones()
		print(sensArray)
		//self.tableView1.reloadData()
		
		self.tableView1.reloadData()
		//self.tableView2.reloadData()
		//self.refresher.endRefreshing()
		
	}
	func refresh2(){
		
		updateSensor()
		updateZones()
		print(sensArray)
		//self.tableView1.reloadData()
		
		self.tableView2.reloadData()
		//self.tableView2.reloadData()
		//self.refresher.endRefreshing()
		
	}


	
	public func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		
		var count:Int?
		
		updateZones()
		updateSensor()
		
		if tableView == self.tableView1 {
			count =  zoneVal.count
		}
		
		if tableView == self.tableView2 {
			if(select == 1){
				count = sensArray.count
			}
			else{
				count = 1
			}
			//
		}
		
		return count!
	}
	

	
	public func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		
		//let cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "cell")
		//cell.textLabel?.text = zoneNames[indexPath.row]
		
		updateZones()
		updateSensor()
		
		var cell:UITableViewCell?
		
		if tableView == self.tableView1 {
			
			cell = tableView.dequeueReusableCell(withIdentifier: "cell1", for: indexPath)
			//cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "cell1")
			cell?.textLabel?.text = zoneVal[indexPath.row].room_des
			cell?.backgroundColor = UIColor.clear
			cell?.textLabel?.textColor = UIColor.black;
			//cell = tableView.dequeueReusableCellWithIdentifier("cell1", forIndexPath: indexPath)
			//let previewDetail = sampleData1[indexPath.row]
			//cell!.textLabel!.text = previewDetail.title
			
		}
		
		if tableView == self.tableView2 {
			
			cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "cell2")
			cell?.backgroundColor = UIColor.clear
			cell?.textLabel?.textColor = UIColor.black;
			
			//let customColorView = [[UIView alloc] init];
			//tableView.backgroundColor = UIColor(red: 62, green: 101, blue: 127, alpha: 1)
			
			
			
			if(select == 1) {
				cell?.textLabel?.text = sensArray[indexPath.row]
				//cell?.selectedBackgroundView?.backgroundColor =  UIColor(red: 62, green: 101, blue: 127, alpha: 1)
				//cell?.
			}
			else {
				
			}
		}

		return(cell!)
	}
	
	public func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath)
	{
		//if tableView == self.tableView1{
		zoneIndex = indexPath.row
		
		//cell?.backgroundColor = UIColor(red: 62, green: 101, blue: 127, alpha: 1)
		
		if tableView == self.tableView1 {
			//let zoneId = Int(zoneVal[indexPath.row].id)
			sensArray.removeAll()
			for i in 0..<sensVal.count {
				if (zoneVal[zoneIndex].id == sensVal[i].zone_id) {
					sensArray.append(sensVal[i].name)
					select = 1
				}
				
			}
			if(sensArray.count == 0){
				select = 0
			}
			refresh2()
			//self.tableView2.reloadData()
		}
		if tableView == self.tableView2 {
			
		}
		//refresh()
		//performSegue(withIdentifier: "segue", sender: self)
	}
	
	public func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
		if tableView == self.tableView1 {
			if editingStyle == UITableViewCellEditingStyle.delete {
				
				
				let preweburl = "http://www.lonelycircuits.se/data/remove_zone.php?remove="
				let zone = zoneVal[indexPath.row].room_des
				let weburl3 = preweburl + zone
				
				let url3 = (URL(string: weburl3))
				
				print(weburl3)
				
				self.webView3.loadRequest(URLRequest(url: url3!))
				
				updateZones()
				updateSensor()
				
				
				//self.tableView1.reloadData()
				zoneVal.remove(at: indexPath.row)
				refresh()
			}
			
		}
		if tableView == self.tableView2 {
			if editingStyle == UITableViewCellEditingStyle.delete {
				
				
				let preweburl = "http://www.lonelycircuits.se/data/remove_sensor.php?remove="
				let zone = sensArray[indexPath.row]
				let weburl3 = preweburl + zone
				
				let url3 = (URL(string: weburl3))
				
				self.webView3.loadRequest(URLRequest(url: url3!))
				
				updateZones()
				updateSensor()
				
				var tempID = 0
				for i in 0..<sensVal.count {
					if (sensArray[indexPath.row] == sensVal[i].name) {
						tempID = i
					}
				}
				
				sensArray.remove(at: indexPath.row)
				sensVal.remove(at: tempID)
				refresh2()
				
			}
		}
		//refresh2()
	}
	
	override func viewDidLoad() {
		super.viewDidLoad()
		updateSensor()
		updateZones()
		
		tableView1.dataSource = self
		tableView1.delegate = self
		tableView1.register(UITableViewCell.self, forCellReuseIdentifier: "cell1")

		tableView2.dataSource = self
		tableView2.delegate = self
		tableView2.register(UITableViewCell.self, forCellReuseIdentifier: "cell2")
	}
	
	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}
	
	@IBAction func addZoneAlert(_ sender: Any) {
	
		let alertController = UIAlertController(title: "Add Zone", message: "Enter the name of your new zone:", preferredStyle: .alert)
		
		//alert.addAction(UIAlertAction(title: "Cancel", style: UIAlertActionStyle.Cancel, handler: nil))
		alertController.addAction(UIAlertAction(title: "Cancel", style: UIAlertActionStyle.cancel, handler: nil))
		
		alertController.addAction(UIAlertAction(title: "Save", style: .default, handler: {
			alert -> Void in
			let zoneTextField = alertController.textFields![0] as UITextField
			//let lNameField = alertController.textFields![1] as UITextField
			
			if zoneTextField.text != "" {
				
				//self.newZone = zoneTextField.text!
				//let addZone = zoneTextField.text!
				let addZone = zoneTextField.text!
				//Add Zone to database
				let baseUrl = "http://www.lonelycircuits.se/data/add_zone.php?zone=%22"
				let tjugo = "%22"
				let fullUrl = baseUrl + addZone + tjugo
				
				let url4 = (URL(string: fullUrl))
				
				self.webView3.loadRequest(URLRequest(url: url4!))

				updateZones()
				updateSensor()

				updateZones()
				updateSensor()
				
				self.refresh()
				self.refresh2()
				
				updateZones()
				updateSensor()
				
				self.refresh()
				self.refresh2()
				
				updateZones()
				updateSensor()
				
				self.refresh()
				self.refresh2()
				

				
				let addedAlert = UIAlertController(title: "Added", message: "The Zone has been added. ", preferredStyle: .alert)
				addedAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
				self.present(addedAlert, animated: true, completion: nil)
				
			} else {
				let errorAlert = UIAlertController(title: "Error", message: "Please input zone name", preferredStyle: .alert)
				errorAlert.addAction(UIAlertAction(title: "OK", style: .cancel, handler: {
					alert -> Void in
					self.present(alertController, animated: true, completion: nil)
				}))
				self.present(errorAlert, animated: true, completion: nil)
			}
		}))
		
		alertController.addTextField(configurationHandler: { (textField) -> Void in
			textField.placeholder = "Zone_Name"
			textField.textAlignment = .center
		})
		
		self.present(alertController, animated: true, completion: nil)
		
		self.refresh()
	}
	
	@IBAction func uppdateTables(_ sender: Any) {
		
		updateZones()
		updateSensor()
		
		refresh()
		refresh2()
	}
	
	
}

