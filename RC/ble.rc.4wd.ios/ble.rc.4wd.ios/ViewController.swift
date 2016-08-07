//
//  ViewController.swift
//  ble.rc.4wd.ios
//
//  Created by 馬 英奎 on 2016/08/07.
//  Copyright © 2016年 馬 英奎. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var webView: UIWebView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        webView.scalesPageToFit = true;
        let url = NSBundle.mainBundle().URLForResource("html/index", withExtension:"html");
        let request = NSURLRequest(URL: url!);
        webView.loadRequest(request);
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func shouldAutorotate() -> Bool{
        return false
    }
    
    func webView(webView: UIWebView, shouldStartLoadWithRequest request: NSURLRequest, navigationType: UIWebViewNavigationType) -> Bool {
        if(request.URL!.scheme == "ble.rc.4wd"){
            return false;
        }
        return true
    }
}

