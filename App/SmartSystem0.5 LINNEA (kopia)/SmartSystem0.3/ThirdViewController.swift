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
	
	var zoneIndex = 0
	var select = 0
	var sensArray = [String]()
	
	
	func refresh(){
		
		print(sensArray)
		self.tableView2.reloadData()
		//self.refresher.endRefreshing()
		
	}
	
	public func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		
		var count:Int?
		
		if tableView == self.tableView1 {
			count =  zoneNames.count
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
		
		var cell:UITableViewCell?
		
		if tableView == self.tableView1 {
			
			cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "cell1")
			cell?.textLabel?.text = zoneNames[indexPath.row]
			//cell = tableView.dequeueReusableCellWithIdentifier("cell1", forIndexPath: indexPath)
			//let previewDetail = sampleData1[indexPath.row]
			//cell!.textLabel!.text = previewDetail.title
			
		}
		
		if tableView == self.tableView2 {
			
			cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: "cell2")
			
			if(select == 1) {
				cell?.textLabel?.text = sensArray[indexPath.row]
			}
			else {
				
			}
			
			//cell?.textLabel?.text = zoneNames[indexPath.row]
			//cell = tableView.dequeueReusableCellWithIdentifier("cell2", forIndexPath: indexPath)
			//let previewDetail = sampleData[indexPath.row]
			//cell!.textLabel!.text = previewDetail.title
			
		}
		
		return(cell!)
	}
	
	
	// MARK: - Table view data source
	/*
	public func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		// #warning Incomplete implementation, return the number of rows
		return zoneNames.count
	}
	
	public func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		
		let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath)
		
		cell.textLabel?.text = zoneNames[indexPath.row]
		
		return cell
	}
	
	*/
	public func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath)
	{
		//if tableView == self.tableView1{
			zoneIndex = indexPath.row
		
			//let zoneId = Int(zoneVal[indexPath.row].id)
			sensArray.removeAll()
			for i in 0..<sensVal.count {
				if (zoneVal[zoneIndex].id == sensVal[i].zone_id) {
					sensArray.append(sensVal[i].name)
					select = 1
				}
				refresh()
			}
		//}
		//performSegue(withIdentifier: "segue", sender: self)
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
	
	
}

