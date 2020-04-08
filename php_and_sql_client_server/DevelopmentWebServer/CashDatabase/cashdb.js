/*

This file is part of Ext JS 4

Copyright (c) 2011 Sencha Inc

Contact:  http://www.sencha.com/contact

Commercial Usage
Licensees holding valid commercial licenses may use this file in accordance with the Commercial Software License Agreement provided with the Software or, alternatively, in accordance with the terms contained in a written agreement between you and Sencha.

If you are unsure which license is appropriate for your use, please contact the sales department at http://www.sencha.com/contact.

*/

Ext.require([
    'Ext.form.*',
    'Ext.form.ComboBox',
    'Ext.Img',
    'Ext.tip.QuickTipManager',
    'Ext.window.Window',
    'Ext.tab.*',
    'Ext.toolbar.Spacer',
    'Ext.layout.container.Card',
    'Ext.layout.container.Border',
    'Ext.button.*',
    'Ext.layout.container.Container',
    'Ext.panel.*',
    'Ext.grid.*',
    'Ext.Direct',
    'Ext.data.*',
    'Ext.util.*',
    'Ext.state.*',
    'Ext.ux.CheckColumn',
    'LevyRequest',
  
]);

Ext.onReady(function() {
	
	start = new StartPage();
	start.CreateNewStartPage();
	//alert("Hide start Page");
	//start.hideStartPage();
	//alert("Init start page");
	
	//start.initialize();
	//alert("Delete start page");
	//start.deleteStartPage();
	//alert("create start page");
	//start.CreateNewStartPage();     
});

function StartPage()
{
	this.formPanel = new Array();
	this.btn = null;
    this.request  = null;
    var that = this;
    this.NUMBER_OF_PANELS = 4;
    this.path = new Array();
    //Each path sets the flow from start page to the end page
    
    // this.path[0] represents the path from the subpanel 0 where the Case Number will be
    // entered
    // the flow for this case is {0} -> {104,105,7,8}
    // the first page after the case search will be entered will display the results of the
    // query with id = 0 defined in classes.php as  $SearchData[0] = new StdClass();
    // the second page will display the results of the queries with  id = {104,105,7,8} defined in
    // classes.php as :
    // $SearchData[104] = new StdClass();, $SearchData[105] = new StdClass();,$SearchData[7] = new StdClass();,$SearchData[8] = new StdClass();
    
    // this.path[1] represents the path from the subpanel 1 where the Levy Number will be
    // entered
    // the flow for this case is {1,3,4,5}
    // the first page after the case search will be entered will display the results of the
    // query with id = {1,3,4,5} defined in classes.php as  
    // $SearchData[1] = new StdClass();, $SearchData[3] = new StdClass();,$SearchData[4] = new StdClass();,$SearchData[5] = new StdClass();
    
    // this.path[2] represents the path from the subpanel 2 where the  Name will be
    // entered
    // the flow for this case is {2} -> {100} -> {200,105,101,201}
    // the first page after the name search will be entered will display the results of the
    // query with id = 2 defined in classes.php as  $SearchData[2] = new StdClass();
    // the second page will display the results of the queries with  id = {100} defined in
    // classes.php as :
    // $SearchData[100] = new StdClass();, 
    // the third page will display the results of the query with id ={200,105,101,201} defined in 
    // classes.php as
    // $SearchData[200] = new StdClass();,$SearchData[105] = new StdClass();,$SearchData[101] = new StdClass();,$SearchData[201] = new StdClass();
    
    // to add new search panel add next case to searchitems to create panel , add  parameters to create search parameters, add this.path
    // with correcponding queries to be displayed, add new WindowTitle for each new window, define datastore for each query to save
    //query data, add case to this.loadStoreData = function() in ConstantValues.js for each defined new query in classes.php,
    // add grid case in grids.js for each grid case to be displayed on a page from the datastore received. The data from data store
    // can be broken down and displayed by different grids or other diplay elements of extjs 4.0 or javascript defined classes.
    //panel 0
    this.path[0] = new Array();
    
    this.path[0][0] = new Array();
    this.path[0][0][0] = 0;
    
    this.path[0][1] = new Array();
    this.path[0][1][0] = 104;
    this.path[0][1][1] = 105;
    this.path[0][1][2] = 7;
    this.path[0][1][3] = 8;
  
    //panel 1
    this.path[1] = new Array();
    
    this.path[1][0] = new Array();
    this.path[1][0][0] = 1;
    this.path[1][0][1] = 3;
    this.path[1][0][2] = 4;
    this.path[1][0][3] = 5;
    
   
    //panel 2
    this.path[2] = new Array();
    
    this.path[2][0] = new Array();
    this.path[2][0][0] = 2;
    
    this.path[2][1] = new Array();
    this.path[2][1][0] = 100;
    
    this.path[2][2] = new Array();
    this.path[2][2][0] = 200;
    this.path[2][2][1] = 105;
    this.path[2][2][2] = 101;
    this.path[2][2][3] = 201;
   
    var that = this;
   
    //panel 3
   /* this.path[3] = new Array();
    
    this.path[3][0] = new Array();
    this.path[3][0][0] = 102;
    this.path[3][0][1] = 103;
    var that = this;*/
    
   this.addSearchCase = function (index,searchname)
	{
		var pan = new Ext.form.Panel(
		{
        		renderTo: Ext.getBody(),
        		scope: this.addSearchCase,
        		frame: true,
        		width: 300,
        		height: 100,
        		bodyPadding: 25,
       			x: 0,
        		y: 0,
     
        		fieldDefaults: {
            		labelAlign: 'top',
            		msgTarget: 'none',
            		invalidCls: '' 
        		},
        
       			items: 
       			[
        				searchname,
        				{
            					xtype: 'button',
            					formBind: true,
            					disabled: false,
            					text: 'search',
            					x: 200,
            					y: -50,
            					handler: function() 
            					{
                    					var form = this.up('form').getForm();
                    					if (form.isValid()) 
                    					{
         										var nextID = new Array();
                   	   							var currentID = new Array();
                   	   							//switch(index)
                   	   							//{
                   	   	   						//case 0:
                   	   	   						//case 1:
                   	   	   						//case 2:
                   	   		        			//alert(that.path[index][0]);
                   	   	   		    			if(that.path[index][0]);
                   	   	       						currentID = that.path[index][0];
                   	   	       	 
                   	   	       					if(that.path[index][1])   
                   	   	       		   				nextID = that.path[index][1];
                   	   	   						//break;
                   	   	   						/*case 1:
                   	   	       						currentID = that.path[index][0];
                   	   	       						nextID = null;
                   	   	   						break;
                   	   	   						case 2:
                   	   	        						currentID = that.path[index][0];
                   	   	        						nextID = that.path[index][1];
                   	   	        		
                   	   	   						break;*/
                   	   	 
                   	   					
                   	   							panelrequests[index] = new Array();
                   	   							for(a=0; a < currentID.length; a++)
                   	   							{
                   	   	   							p= new PanelURLRequestData();
                   	   	   							p.setParameters(WindowTitles[index],currentID,nextID,that.path[index],0);
                   	   	   
                   	   	   							for(i = 0;i < search[index][a].length; i++)
                   	   			 					{
                   	   			 	 					 var formtext;
                   	   			 	   					if(search[index][a][i] == 'rstart')
                   	   			 	   		 				formtext = form.findField('receiptstart');
                   	   			 	   					else if(search[index][a][i] == 'rend')
                   	   			 	          					formtext = form.findField('receiptend');
                   	   			 	   					else
                   	   						  					formtext = form.findField(search[index][a][i]);
                   	   				   					if(search[index][a][i] == 'levymaster' || search[index][a][i] == 'levyaccounts' || search[index][a][i] == 'levyhistory' || search[index][a][i] == 'levydetail')
                   	   				         					formtext = form.findField("levy");
                   	   		    						p.pushNames(search[index][a][i]);
                   	   	                				p.pushValues(formtext.getValue());
                   	   					 		}
                   	   	        
                   	   							url = p.buidurl(  phpurl, p.getpValues() , p.getpNames() );
                   	   		 					p.seturl(url);
                   	  		    				(panelrequests[index]).push(p); 	
                   	  		    				delete(p);
                   	   							}
                   	   							that.hideStartPage();
                   	   							that.request = new LevyRequest();
                   	   							//uncomment  this.testRequest to test if the data is correctly initialized
                   	   							//this.testRequest = function(panelrequests[index],index);
                   	   							that.request.postRequest(panelrequests[index],index);
                   	   							that.request.getRequest(panelrequests[index],index);
                    					}
            					}
        				}
        
             ]
		});
	    return pan;
	}
	
    this.initialize =  function()
	{
		 
		  //alert("Initialize NEW SEARCH");	
		  if(this.request)
		     delete(this.request);
		  while(panelrequests.length > 0)
		         panelrequests.pop();
		  this.showStartPage();
		  
		
            
	}  
	 this.CreateNewStartPage =  function()
	{
           // this.formPanel = new Array();   
               
            for(var i=0; i < searchitems.length;i++)
            {
            	if(!this.formPanel[i])
       		   			this.formPanel.push(this.addSearchCase(i,searchitems[i]));
       		   	else
       		   	{
       		   		for(var j=0; j< this.formPanel.length; j++)
       		   			this.formPanel[j].show();
       		   	}
            }
       		//this.formPanel.push(this.addSearchCase(i,searchitems[3]));
       	
       		//var fieldnames = new Array();
       		//fieldnames[0] = "receipttotals";
       		//var fieldvalues = new Array();
       		//fieldvalues[0] = 500;
           // this.addBtn("Receipt Totals",500,fieldvalues,fieldnames);
	} 
	this.hideStartPage  = function()
	{
		if(this.btn)
			this.btn.hide();
		if(this.formPanel)
		{
			for(var i=0;i < this.formPanel.length;i++)
					this.formPanel[i].hide();
		}
	}
	this.showStartPage  = function()
	{
		if(this.btn)
			this.btn.show();
		    
		if(this.formPanel)
		{
			for(var i=0;i < this.formPanel.length;i++)
				this.formPanel[i].show();
		}
	}
	this.deleteStartPage  = function()
	{
		if(this.request)
		   delete(this.request);
		if(this.btn)
		{
			this.btn.hide();
		    delete(this.btn);
		}
		if(this.formPanel)
		{
			for(var i=0;i < this.formPanel.length;i++)
			{
				 this.formPanel[i].hide();
			     delete(this.formPanel[i]);
			}
			delete(this.formPanel);
		}
	}
	this.addBtn = function addBtn(name,index,fieldvalues,fieldnames)
    {
         this.btn =      new Ext.Button( {  
                //icon   : 'icons/back.png',
    		    text: name,
                height: 25,
                width:  100,
                x: 50,
                y: 75,
                renderTo: Ext.getBody(),        
                handler: function() {
                	
                	 			this.request = new LevyRequest();
                	 			this.hideStartPage();
                	 			alert("Finished btnmmmm");
                	  			//for(i=0;i< formPanel.length;i++)
                        				//this.formPanel[i].hide();
                				//this.btn.hide();
                	 			
                	 			
                     			//this.request.getRequest(this.request.postRequest(phpurl,fieldvalues,fieldnames),index); 
                }
              }); 
              this.btn.show();
             
    	//return btn;
           
    }
}
     