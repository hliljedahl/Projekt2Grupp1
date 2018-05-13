//
//  updateAll.swift
//  SmartSystem0.3
//
//  Created by Hampus Liljedahl on 2018-04-17.
//  Copyright © 2018 LiljedahlLabs. All rights reserved.
//

import Foundation
import UIKit
import Charts

func updateZones(){
	
	let jsonUrlString = "http://lonelycircuits.se/data/json_zone.php"
	guard let url = URL(string: jsonUrlString) else { return }
	
	URLSession.shared.dataTask(with: url) { (data, response, err) in
		//perhaps check err
		//also perhaps check response status 200 OK
		
		guard let data = data else { return }
		
		do {
			
			let zonevalues = try JSONDecoder().decode([Zone].self, from: data)
			
			//print(zonevalues[1].room_des)
			//var test = [String]()
			
			zoneVal = zonevalues
		//	print(zoneVal)
			for i in 0..<zoneVal.count {
				
				zoneNames.append(String(zoneVal[i].room_des))
				//print(zoneVal[i].room_des)
				//print(zoneNames[i])
			}
			//print(zoneVal[1].room_des)
			
		} catch let jsonErr {
			print("Error serializing json:", jsonErr)
		}
		
		
		
		}.resume()
	// Do any additional setup after loading the view, typically from a nib.
	
}
func updateData(){
	
	let jsonUrlString = "http://lonelycircuits.se/data/json_data.php"
	guard let url = URL(string: jsonUrlString) else { return }
	
	URLSession.shared.dataTask(with: url) { (data, response, err) in
		//perhaps check err
		//also perhaps check response status 200 OK
		
		guard let data = data else { return }
		
		//            let dataAsString = String(data: data, encoding: .utf8)
		//            print(dataAsString)
		
		do {
			
			let datavalues = try JSONDecoder().decode([Data].self, from: data)
			
			//print(datavalues[1].value)
			//var test = [String]()
			
			//dataVal.append(contentsOf: datavalues)
			dataVal = datavalues
			
			
		} catch let jsonErr {
			print("Error serializing json:", jsonErr)
		}
		
		
		
		}.resume()
	// Do any additional setup after loading the view, typically from a nib.
	
}

func updateSensor(){
	
	let jsonUrlString = "http://lonelycircuits.se/data/json_sensors.php"
	guard let url = URL(string: jsonUrlString) else { return }
	
	URLSession.shared.dataTask(with: url) { (data, response, err) in
		//perhaps check err
		//also perhaps check response status 200 OK
		
		guard let data = data else { return }
		
		do {
			
			let sensorvalues = try JSONDecoder().decode([Sensor].self, from: data)
			
			//print(datavalues[1].value)
			//var test = [String]()
			
			sensVal = sensorvalues
			
			
		} catch let jsonErr {
			print("Error serializing json:", jsonErr)
		}
		
		
		
		}.resume()
	// Do any additional setup after loading the view, typically from a nib.
	
}

func updateInst(){
	
	let jsonUrlString = "http://lonelycircuits.se/data/json_inst.php"
	guard let url = URL(string: jsonUrlString) else { return }
	
	URLSession.shared.dataTask(with: url) { (data, response, err) in
		//perhaps check err
		//also perhaps check response status 200 OK
		
		guard let data = data else { return }
		
		do {
			
			let instvalues = try JSONDecoder().decode([Inst].self, from: data)
			
			//print(datavalues[1].value)
			//var test = [String]()
			
			instVal = instvalues
			
			for i in 0..<instVal.count {
				
				instMax.append(String(instVal[i].max))
				//print(zoneVal[i].room_des)
				//print(zoneNames[i])
			}

			
			
		} catch let jsonErr {
			print("Error serializing json:", jsonErr)
		}
		
		
		
		}.resume()
	// Do any additional setup after loading the view, typically from a nib.
	
}


