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
var zoneNames = [String]()
var zoneID = 0

class SecondViewController: UIViewController{

	@IBOutlet weak var lineChart: LineChartView!
	@IBOutlet weak var lineChart2: LineChartView!
	var drop: UIDropDown!
	@IBOutlet weak var label: UILabel!
	
	@IBAction func allZones(_ sender: UIButton) {
		zoneID = 0
		self.label.text = "Display single zone:"
		drop.placeholder = "Select your zone..."
		updateGraph()
	}
	
	//var list = ["1","2","3","4"]
	
	

	//weak var axisFormatDelegate: IAxisValueFormatter?
	//var input = 10.0

	//var numbers : [Double] = [] //This is where we are going to store all the numbers. This can be a set of numbers that come from a Realm database, Core data, External API's or where ever else
	
	
	
	override func viewDidLoad() {
		super.viewDidLoad()
		updateGraph()
	

		print(zoneNames)
		
		drop = UIDropDown(frame: CGRect(x: 300, y: 200, width: 250, height: 30))
		drop.center = CGPoint(x: 595, y: 100)
		drop.placeholder = "Select your zone..."
		drop.options = zoneNames  //["Mexico", "USA", "England", "France", "Germany", "Spain", "Italy", "Canada"]
		drop.didSelect { (option, index) in
			self.label.text = "You just selected zone: \(option)"
			zoneID = Int(zoneVal[index].id)!
			self.updateGraph()
			print("You just select: \(option) at index: \(index)")
		}
		self.view.addSubview(drop)
		//axisFormatDelegate = self as! IAxisValueFormatter
		
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
		updateInst()
		
		
		//var input = [Double]()
		
		for i in 0..<dataVal.count {
			
			numbers.append(Double(dataVal[i].value)!)
			
		}
		
		//numbers.append(contentsOf: input)
		
		let data = LineChartData() //This is the object that will be added to the chart
		let data2 = LineChartData() //This is the object that will be added to the chart
		
		updateSensor()
		
		var placeArr = [Double]()
		var place = 1.0
		
		placeArr.append(place)
		
		for val in 1..<dataVal.count {
			let currentTime = Int(dataVal[val].timestmp)
			if currentTime ==  Int(dataVal[val-1].timestmp){
				placeArr.append(place)
			}
			/*else if currentTime!+1 ==  Int(dataVal[val-1].timestmp){
				placeArr.append(place)
			}
			else if currentTime!-1 ==  Int(dataVal[val-1].timestmp){
				placeArr.append(place)
			}*/
			else {
				place = place + 1
				placeArr.append(place)
			}
		}
		
		//print(placeArr)
		
		//For loop goes thru every sensor.
		for sens in 0..<sensVal.count {
			var sensData = [Double]()
			
			var placeArrSens = [Double]()
			var testPlaceArr = [Double]()	//
			
			if zoneID != 0 {
				for new in 0..<dataVal.count {
					if sensVal[sens].id == dataVal[new].sensor_id {
						for _ in 0..<zoneVal.count {
							if Int(sensVal[sens].zone_id)!==zoneID{
								//var doubleVal =(dataVal[new].value)
								sensData.append(Double(dataVal[new].value)!)
								testPlaceArr.append(Double(dataVal[new].timestmp)!) //
								placeArrSens.append(placeArr[new])
							}
						}
					}
				}
			}
			else {
				for new in 0..<dataVal.count {
					
					if sensVal[sens].id == dataVal[new].sensor_id {
						//var doubleVal =(dataVal[new].value)
						sensData.append(Double(dataVal[new].value)!)
						testPlaceArr.append(Double(dataVal[new].timestmp)!) //
						placeArrSens.append(placeArr[new])
					}
					
				}

			}
			

			
			
			
			
			var lineChartEntry  = [ChartDataEntry]() //this is the Array that will eventually be displayed on the graph.
			
			//here is the for loop
			for i in 0..<sensData.count {
				//print(i)
				//print(sensData.count)
				
				let value = ChartDataEntry(x: placeArrSens[i], y: sensData[i]) // here we set the X and Y status in a data chart entry
				
				lineChartEntry.append(value) // here we add it to the data set
				
			}
			
			var col = sens
			
			while col >= colorArray.count{
				col = col - colorArray.count
			}
			
			//print(sensVal[sens].type.characters.first?.description ?? "")
			var t = "Temp"
			//print(t.characters.first?.description ?? "")

			if sensVal[sens].type.characters.first?.description ?? "" == t.characters.first?.description ?? "" {
				let line1 = LineChartDataSet(values: lineChartEntry, label: sensVal[sens].name) //Here we convert lineChartEntry to a LineChartDataSet
				line1.colors = [colorArray[col]] //Sets the colour to blue
				line1.setCircleColor(colorArray[col])
				data.addDataSet(line1) //Adds the line to the dataSet
			}else {
				let line2 = LineChartDataSet(values: lineChartEntry, label: sensVal[sens].name) //Here we convert lineChartEntry to a LineChartDataSet
				line2.colors = [colorArray[col]] //Sets the colour to blue
				line2.setCircleColor(colorArray[col])
				data2.addDataSet(line2) //Adds the line to the dataSet
				
			}
			
		}
		
		lineChart.data = data //finally - it adds the chart data to the chart and causes an update
		lineChart.chartDescription?.text = " " // Here we set the description for the graph
		lineChart2.data = data2 //finally - it adds the chart data to the chart and causes an update
		lineChart2.chartDescription?.text = " " // Here we set the description for the graph


		
		/*
		for i in 0..<numbers.count {
		numbers[i]=0
		}*/
		
		//updateGraph(number: numbers)
		
		//print(numbers)
	}


	
}

