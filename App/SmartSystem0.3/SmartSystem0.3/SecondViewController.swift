//
//  SecondViewController.swift
//  SmartSystem0.3
//
//  Created by Hampus Liljedahl on 2018-04-17.
//  Copyright © 2018 LiljedahlLabs. All rights reserved.
//

import UIKit
import Charts

class SecondViewController: UIViewController {

	@IBOutlet weak var lineChart: LineChartView!
	var input = 10.0

	var numbers : [Double] = [] //This is where we are going to store all the numbers. This can be a set of numbers that come from a Realm database, Core data, External API's or where ever else

	
	
	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
	}
	
	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	@IBAction func updButton(_ sender: Any) {
		input = input + 0.5
		numbers.append(input)
		
		updateGraph()
	}
	
	func updateGraph(){
		var lineChartEntry  = [ChartDataEntry]() //this is the Array that will eventually be displayed on the graph.
		
		
		//here is the for loop
		for i in 0..<numbers.count {
			
			let value = ChartDataEntry(x: Double(i), y: numbers[i]) // here we set the X and Y status in a data chart entry
			lineChartEntry.append(value) // here we add it to the data set
			
		}
		
		let line1 = LineChartDataSet(values: lineChartEntry, label: "Temperature") //Here we convert lineChartEntry to a LineChartDataSet
		line1.colors = [NSUIColor.blue] //Sets the colour to blue
		line1.setCircleColor(NSUIColor.blue)

		
		let data = LineChartData() //This is the object that will be added to the chart
		data.addDataSet(line1) //Adds the line to the dataSet
		
		
		
		lineChart.data = data //finally - it adds the chart data to the chart and causes an update
		lineChart.chartDescription?.text = "Testing testing..." // Here we set the description for the graph
	}
	
}

