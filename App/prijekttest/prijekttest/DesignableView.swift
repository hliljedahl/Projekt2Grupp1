//
//  DesignableView.swift
//  prijekttest
//
//  Created by Linnea Björck on 2018-04-26.
//  Copyright © 2018 Linnea Björck. All rights reserved.
//

import UIKit

@IBDesignable class DesignableView: UIView {
    
    @IBInspectable var cornerRadius: CGFloat = 0 {
        didSet{
            self.layer.cornerRadius = cornerRadius
            
        }
        
    }


}
