//
//  NewViewController.swift
//  
//
//  Created by Cameron Flannery on 10/1/16.
//
//

import UIKit

class NewViewController: UIViewController {

    @IBOutlet weak var titleLabel: UILabel!
    
    var titleSrting: String!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.titleLabel.text  = self.titleSrting
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
