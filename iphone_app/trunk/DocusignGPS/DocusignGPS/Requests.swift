//
//  Requests.swift
//  DocusignGPS
//
//  Created by Cameron Flannery on 10/1/16.
//  Copyright © 2016 SDHacks. All rights reserved.
//

import Foundation
import FirebaseDatabase

struct Requests {
    let isNewRequest: Bool!
    let isAuthorized: Bool!
    let lat: Double!
    let long: Double!
    let responseRecieved: Bool!
    let itemRef: FIRDatabaseReference?
    
    init (isNewRequest: Bool, isAuthorized: Bool, lat: Double, long: Double, responseRecieved: Bool) {
        self.isNewRequest = isNewRequest
        self.isAuthorized = isAuthorized
        self.lat = lat
        self.long = long
        self.responseRecieved = responseRecieved
        
        itemRef = nil
    }
    
    init (snapshot: FIRDataSnapshot) {
        
 /*
        key = snapshot.key
        itemRef = snapshot.ref
        
        let value = snapshot.value as? NSDictionary
        let statusContent = value?["content"] as? String
        let statusUser = value?["addedByUser"] as? String
        content = statusContent
        addedByUser = statusUser
 */
    }
    
    /*
    func toAnyObject() -> NSDictionary {
        return ["content": content, "addedByUser": addedByUser] as NSDictionary
    }
 */
}
