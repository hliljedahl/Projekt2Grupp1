//
//  SecondViewController.swift
//  SmartSystem0.3
//
//  Created by Hampus Liljedahl on 2018-04-17.
//  Copyright © 2018 LiljedahlLabs. All rights reserved.
//

import UIKit
import Charts

var colorArray = [NSUIColor.red, NSUIColor.purple, NSUIColor.black, NSUIColor.blue, NSUIColor.orange, NSUIColor.green, NSUIColor.darkGray, NSUIColor.brown, NSUIColor.yellow, NSUIColor.cyan]

struct Data: Decodable {
	let sensor_id: String
	let timestmp: String
	let value: String
}

struct Sensor: Decodable {
	let id: String
	let name: String
	let zone_id: String
	let type: String
}

struct Zone: Decodable {
	let id: String
	let room_des: String
}

var dataVal = [Data]()
var sensVal = [Sensor]()
var zoneVal = [Zone]()

class SecondViewController: UIViewController {

	@IBOutlet weak var lineChart: LineChartView!
	//var input = 10.0

	//var numbers : [Double] = [] //This is where we are going to store all the numbers. This can be a set of numbers that come from a Realm database, Core data, External API's or where ever else

	
	
	override func viewDidLoad() {
		super.viewDidLoad()
		
	}
	
	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	@IBAction func updButton(_ sender: Any) {
		
		updateGraph()
		
	}
	
	func updateGraph(){
		var numbers = [Double]()
		
		updateData()
		updateSensor()
		
		var input = [Double]()
		
		for i in 0..<dataVal.count {
			
			input.append(Double(dataVal[i].value)!)
			
		}
		
		numbers.append(contentsOf: input)
		
		let data = LineChartData() //This is the object that will be added to the chart
		
		for sens in 0..<sensVal.count {
			
			var sensData = [Double]()
			
			for new in 0..<dataVal.count {
				
				if sensVal[sens].id == dataVal[new].sensor_id {
					//var doubleVal =(dataVal[new].value)
					sensData.append(Double(dataVal[new].value)!)
				}
				
			}
			
			
			var lineChartEntry  = [ChartDataEntry]() //this is the Array that will eventually be displayed on the graph.
			
			//here is the for loop
			for i in 0..<sensData.count {
				
				let value = ChartDataEntry(x: Double(i), y: sensData[i]) // here we set the X and Y status in a data chart entry
				lineChartEntry.append(value) // here we add it to the data set
				
			}
			
			let line1 = LineChartDataSet(values: lineChartEntry, label: sensVal[sens].name) //Here we convert lineChartEntry to a LineChartDataSet
			
			var col = sens
			
			while col >= colorArray.count{
				col = col - colorArray.count
			}
			
			line1.colors = [colorArray[col]] //Sets the colour to blue
			line1.setCircleColor(colorArray[col])
			
			
			data.addDataSet(line1) //Adds the line to the dataSet
			
		}
		
		
		lineChart.data = data //finally - it adds the chart data to the chart and causes an update
		lineChart.chartDescription?.text = "Testing testing..." // Here we set the description for the graph
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*
		for i in 0..<numbers.count {
		numbers[i]=0
		}*/
		
		//updateGraph(number: numbers)
		
		//print(numbers)
	}
	

	
}

