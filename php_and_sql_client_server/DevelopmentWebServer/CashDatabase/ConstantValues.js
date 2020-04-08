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

]);

    var start;
   var currentpanels= new Array();
   var countpanels = 0;
   var panelrequests = new Array();
   var currentpanel = new Array();  
   var currentwindow= null;
   var mainwindow = null;
   
    var phpurl = 'http://localhost:8080/CashLevy/SearchLevy.php';
   
    var dataset = new Array();
    
    //search array adds the nearch case to the start page
    // used in cashdb.jc to add new panel for the search case
    var search = new Array();
    //panel 0 
    search[0] = new Array();
     search[0][0] = new Array();
      search[0][0][0] = "casenum";
   //panel 1
    search[1] = new Array();
    
     search[1][0] = new Array();
      search[1][0][0] = "levymaster";
      
       search[1][1] = new Array();
      search[1][1][0] = "levyaccounts";
      
      search[1][2] = new Array();
      search[1][2][0] = "levyhistory";
      
      search[1][3] = new Array();
      search[1][3][0] = "levydetail";
   //panel 2
    search[2] = new Array();
     search[2][0] = new Array();
      search[2][0][0] = "name";
   //panel 3
   // search[3] = new Array();
    // search[3][0] = new Array();
     // search[3][0][0] = "receiptstart";
      //search[3][0][1] = "receiptend";
    // search[3][1] = new Array();
     // search[3][1][0] = "rstart";
     // search[3][1][1] = "rend";
   //
   // parameters -> add the each query search case parameters 
   // used in grids.js function this.createnextPage =  function(rec) to create the request parameters
   // for the next requested page. The request initialized by clicking the button and handled  by the
   // handler:  in each grid case.
   //Panels post  and get url names 
      parameters = new Array();
      //panel 0
      
      parameters[0] = new Array();
      // parameters post
      parameters[0][0] = new Array();
      parameters[0][0][0] = "casenum";
      
      
      //parameters get
      parameters[0][1] = new Array();
      parameters[0][1][0] = "casenum";
        //panel 1
      
      parameters[1] = new Array();
      // parameters post
      parameters[1][0] = new Array();
      parameters[1][0][0] = "levymaster";
      
      
      //parameters get
      parameters[1][1] = new Array();
      parameters[1][1][0] = "levy";
      
     
        //panel 2
      
      parameters[2] = new Array();
      // parameters post
      parameters[2][0] = new Array();
      parameters[2][0][0] = "name";
      
      
      //parameters get
      parameters[2][1] = new Array();
      parameters[2][1][0] = "name";
      
      //panel 3 levy accounts
      parameters[3] = new Array();
      // parameters post
      parameters[3][0] = new Array();
      parameters[3][0][0] = "levyaccounts";
      
      
      //parameters get
      parameters[3][1] = new Array();
      parameters[3][1][0] = "levynum";
      
      //levy 4 history data
      
      parameters[4] = new Array();
      // parameters post
      parameters[4][0] = new Array();
      parameters[4][0][0] = "levyhistory";
      
      
      //parameters get
      parameters[4][1] = new Array();
      parameters[4][1][0] = "levy";
      
      //panel 5 levy receipts detail section
      parameters[5] = new Array();
      // parameters post
      parameters[5][0] = new Array();
      parameters[5][0][0] = "levydetail";
      
      
      //parameters get
      parameters[5][1] = new Array();
      parameters[5][1][0] = "recpt";
      
      
      
      //Levy History
      parameters[7] = new Array();
      // parameters post
      parameters[7][0] = new Array();
      parameters[7][0][0] = "levyhistoryfinal";
      
      
      //parameters get
      parameters[7][1] = new Array();
      parameters[7][1][0] = "levy";
      
      //Receipts Detail Section

      parameters[8] = new Array();
      // parameters post
      parameters[8][0] = new Array();
      parameters[8][0][0] = "levydetailfinal";
      
      
      //parameters get
      parameters[8][1] = new Array();
      parameters[8][1][0] = "levy";
       //panel 100
      
      parameters[100] = new Array();
      // parameters post
      parameters[100][0] = new Array();
      parameters[100][0][0] = "nameid100";
      parameters[100][0][1] = "casenumid100";
      
      //parameters get
      parameters[100][1] = new Array();
      parameters[100][1][0] = "name";
      parameters[100][1][1] = "casenum";
      
      //panel 101 history records when levy and name selected
      
      parameters[101] = new Array();
       // parameters post
      parameters[101][0] = new Array();
      parameters[101][0][0] = "levynumid101";
      parameters[101][0][1] = "nameid101";
      
      //parameters get
      parameters[101][1] = new Array();
      parameters[101][1][0] = "levy";
      parameters[101][1][1] = "name";
      
      
       //panel 104  Levy Master
      
      parameters[104] = new Array();
      // parameters post
      parameters[104][0] = new Array();
      parameters[104][0][0] = "casenumbermasterfinal";
      parameters[104][0][1] = "levymasterfinal";
      
      //parameters get
      parameters[104][1] = new Array();
      parameters[104][1][0] = "casenum";
      parameters[104][1][1] = "levy";
      
        //panel 105  Levy Accounts
      
      parameters[105] = new Array();
      // parameters post
      parameters[105][0] = new Array();
      parameters[105][0][0] = "caseaccountfinal";
      parameters[105][0][1] = "levyaccountsfinal";
      
      //parameters get
      parameters[105][1] = new Array();
      parameters[105][1][0] = "casenum";
      parameters[105][1][1] = "levy";
      
      // panel 200 name, casenum, levy selected to get master record
      
      parameters[200] = new Array();
      // parameters post
      parameters[200][0] = new Array();
      parameters[200][0][0] = "nameid200";
      parameters[200][0][1] = "casenumid200";
      parameters[200][0][2] = "levyid200";
      
      //parameters get
      parameters[200][1] = new Array();
      parameters[200][1][0] = "name";
      parameters[200][1][1] = "casenum";
      parameters[200][1][2] = "levy";
      
      //panel 201 Receipt Detail data when casenum, levy name selected
      
      parameters[201] = new Array();
      // parameters post
      parameters[201][0] = new Array();
      parameters[201][0][0] = "casenumid201";
      parameters[201][0][1] = "levyid201";
      parameters[201][0][2] = "nameid201";
      
      //parameters get
      parameters[201][1] = new Array();
      parameters[201][1][0] = "casenum";
      parameters[201][1][1] = "levy";
      parameters[201][1][2] = "name";
      
     
   var WindowTitles = new Array();
   WindowTitles[0] = "Case Window";
    WindowTitles[1] = "Levy Master Window";
     WindowTitles[2] = "Name Window";
      WindowTitles[3] = "Levy Accounts Window";
       WindowTitles[4] = "Levy History Window";
        WindowTitles[5] = "Receipt Detail Window";
         WindowTitles[6] = "Final receipt detail ";
          WindowTitles[7] = "Levy History Window";
           WindowTitles[8] = "Receipt Detail Window";
            WindowTitles[100] = "Levy Totals Window";
             WindowTitles[101] = "Levy History Window";
               WindowTitles[103] = "Receipts total";
                WindowTitles[104] = "Levy Master Window";
                 WindowTitles[105] = "Levy Accounts Window";
                  WindowTitles[200] = "Levy Master Window";
                   WindowTitles[201] = "Receipt Detail Window";
                 
    Ext.regModel('LevyData', {
    fields: [
         {name: 'id', type: 'integer'},
         {name: 'root', type: 'string'},
         {name: 'name', type: 'string'},
         {name: 'fieldnames', type: 'array'},
         {name: 'data', type: 'array'},
     ]
	});
	 ncols = 5;
	  Ext.define('LevyStore', {
	  	 extend: 'Ext.data.ArrayStore',
         model: 'LevyData',
         autoDestroy : true,
         data: [
         			setNullData(ncols)
               ]
       });
       Ext.regModel('NameData', {
    	fields: [
         {name: 'name', type: 'string'},
         {name: 'casenum', type: 'string'},
         {name: 'levy', type: 'integer'},
     	]
	   });
	   ncols = 2;
	   Ext.define('NameStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'NameData',
         data: [
                	setNullData(ncols)
               ]
	   });
	   
	   Ext.regModel('CaseData', {
    	fields: [
         {name: 'casenum', type: 'string'},
         {name: 'levy', type: 'integer'},
     	]
		});
	   ncols = 2;
	   Ext.define('CaseStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'CaseData',
         data: [
         			setNullData(ncols)
               ]
	   });
	 
	    Ext.regModel('NameCaseData', {
    	fields: [
         {name: 'levy', type: 'integer'},
         {name: 'casenum', type: 'string'},
         {name: 'name', type: 'string'},
     	]
	   });
	    ncols = 3;
	    Ext.define('NameCaseStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'NameCaseData',
         data: [
         			setNullData(ncols)
               ]
	   });
	   
	    Ext.regModel('MasterReceiptData', {
    	fields: [
         {name: 'casenum', type: 'string'},
         {name: 'count1', type: 'string'},
         {name: 'division', type: 'string'},
         {name: 'agency', type: 'string'},
         {name: 'ref_no', type: 'string'},
         {name: 'levy', type: 'integer',useNull:true},
         {name: 'outstanding_rcpt', type: 'string'},
         {name: 'department', type: 'string'},
         {name: 'name', type: 'string'},
         {name: 'addr1', type: 'string'},
         {name: 'addr2', type: 'string'},
         {name: 'payor', type: 'string'},
         {name: 'payor_addr1', type: 'string'},
         {name: 'payor_addr2', type: 'string'},
         {name: 'payor_addr3', type: 'string'},
         {name: 'payor_spn', type: 'string'},
         {name: 'assess_dt', type: 'string'},
         {name: 'status', type: 'string'},
         {name: 'stat_dt', type: 'string'},
         {name: 'tot_fin', type: 'float'},
         {name: 'fin_pd', type: 'float'},
         {name: 'fin_idx', type: 'string'},
         {name: 'lev_stat', type: 'string'},
         {name: 'disp_dt', type: 'string'}, 
         {name: 'note_sent', type: 'string'},
         {name: 'source', type: 'string'},
         
     	]
	   });
	    ncols = 26;
	    n = [5,19,20];
	    
	    Ext.define('MasterReceiptStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'MasterReceiptData',
	   	 groupField: 'casenum',
         data: [ 
        			 
         			 setNullData(ncols)
               ]
	   });
	   Ext.regModel('HistoryReceiptData', {
    	fields: [
         {name: 'levy', type: 'string'},
         {name: 'receipt', type: 'string'},
         {name: 'valid', type: 'string'},
         {name: 'fhs_date', type: 'string'},
         {name: 'amount', type: 'float'},
         {name: 'source', type: 'string'},
     	]
	   });
	    ncols = 6;
	   
	    Ext.define('HistoryReceiptStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'HistoryReceiptData',
	   	 groupField: 'levy',
         data: [
         			setNullData(ncols)
               ]
	   });
	    Ext.regModel('AccountReceiptData', {
    	fields: [
         {name: 'casenum', type: 'string'},
         {name: 'count1', type: 'string'},
         {name: 'division', type: 'string'},
         {name: 'agency', type: 'string'},
         {name: 'levynum', type: 'integer'},
         {name: 'arr_idx', type: 'string'},
         {name: 'screen', type: 'string'},
         {name: 'level', type: 'string'},
         {name: 'fund', type: 'string'},
         {name: 'objt', type: 'string'},
         {name: 'org_amt', type: 'float'},
         {name: 'new_amt', type: 'float'},
         {name: 'pd_amt',type: 'float'},
         {name: 'source',type: 'string'},
     	]
	   });
	    ncols = 14;
	    Ext.define('AccountReceiptStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'AccountReceiptData',
	   	 groupField: 'casenum',
         data: [
         			setNullData(ncols)
               ]
	   });
	    Ext.regModel('FinalReceiptData', {
    	fields: [
         {name: 'recpt', type: 'string'},
         {name: 'casenum', type: 'string'},
         {name: 'count1', type: 'integer'},
         {name: 'scrn', type: 'string'},
         {name: 'fund', type: 'string'},
         {name: 'objt', type: 'string'},
         {name: 'amount', type: 'float'},
         {name: 'dat_src', type: 'date'},
     	]
	   });
	    ncols = 8;
	    Ext.define('FinalReceiptStore', {
	   	 extend: 'Ext.data.ArrayStore',
	   	 model: 'FinalReceiptData',
	   	 groupField: 'recpt',
         data: [
          			setNullData(ncols)
               ]
	   });
	   function setNullData(numberOfColumns)
	   {
	   	
	   	     tempdata = new Array();
	   		 for(i=0;i < numberOfColumns;i++)
	   		 		tempdata[i] = 'NULL';
	   	     return tempdata;
	   }
	   //search items for each query display the panel with parameters that will be passeed to a query
	   // to add more search panels just add next searchitems
	   // if the panel needs mothe then one parameter uncomment example  searchitems[3]
	   // then add case number in cashdb.js to 
	   // this.addSearchCase
	   // add new panel data to p= new PanelURLRequestData();
	   // in loop for(a=0; a < currentID.length; a++)
	   // loop sets the data for the LevyRequest object that initiated next
	   // the data that is sets are parameters that will be passes to a query;
	   // then LevyRequest oblect builds the url out of parameters values
	   // and sent the request to php server, then gets the request and process it data.
	   // php server has JSON string created on corresponding url
	   // this string will be red by getRequest() function that will call the processRequest
	   // function to process the requested data.
	   searchitems = new Array();
	   //items for panel search by case
	   
	   searchitems[0] = {
            xtype: 'textfield',
            name : 'casenum',
            fieldLabel: 'Case Number',
            fieldWidth: 60,
            allowBlank: true,
            //minLength: 10,
            x: 0,
            y: -25
            };
         //items for panel search by receipt
      
        searchitems[1] = {
            xtype: 'textfield',
            name : 'levy',
            fieldLabel: 'Levy Number',
            fieldWidth: 60,
            allowBlank: true,
            //minLength: 10,
            x: 0,
            y: -25
            };
         //items for panel search by name  
        
        searchitems[2] = {
            xtype: 'textfield',
            name : 'name',
            fieldLabel: 'Name',
            fieldWidth: 60,
            allowBlank: true,
            //minLength: 10,
            x: 0,
            y: -25
            };
          //items for panel Conversion receipt Distribution
         /* searchitems[3] = new Array();
          searchitems[3][0] = {
            xtype: 'textfield',
            name : 'receiptstart',
            fieldLabel: 'receiptstart',
            fieldWidth: 60,
            allowBlank: true,
            //minLength: 10,
            x: 0,
            y: -25,
            };
           searchitems[3][1] = {
            xtype: 'textfield',
            name : 'receiptend',
            fieldLabel: 'receiptend',
            fieldWidth: 60,
            allowBlank: true,
            //minLength: 10,
            x: 0,
            y: -25,
            }; */
            
     // Class LevyRequest 
     // The object will be created dynamiccaly with this class to initialize the request for each requested query
     // query defined in CashLevy\classes.php
     // query run from CashLevy\SearchLevy.php
	function LevyRequest()
	{
		var that = this;
		
		this.postRequest = function(panel,index)
		{	
			var s="";
			s= s+ "Post Panel Length = " + panel.length + "\n";
			for(var i=0;i<panel.length;i++)
			{
				s= s+ " url = " + panel[i].geturl();
	   			Ext.Ajax.request(
				{
  					loadMask: true,
  					url: panel[i].geturl(),
  					method: 'POST',
  					success: function(result, request)
  					{
    				
  					}
				})
			}
			// uncomment to test the post address
			//copy and paste the url into the browser to test
			//if the data were received and not equal to null
			//alert(s);
		};
		this.testRequest = function(panel,index)
		{
			alert("Test Panel Length = " + panel.length);
			for(var i=0 ;i < panel.length; i++)
			{
			    panel[i].printURL();
			    w=panel[i].getCurrentID();
			    alert("W= " + w.length);
                panel[i].getNextID();
                panel[i].getPathArray();
                panel[i].getCurrentPathIndex();
			}
		}
		this.sleep = function sleep(milliseconds) 
		{
  				var start = new Date().getTime();
  				for (var i = 0; i < 1e7; i++) 
  					{
   			 			if ((new Date().getTime() - start) > milliseconds){
      						break;
   			 		}
  				}
		}
		this.getRequest = function (panels,index)
		{
			//alert("START REQUEST");
		     if(panels)
        	{
        			getreqMethod = function (i)
        			{
        				//alert("i= " + i);
        				if(i == panels.length)
				  		 {
                                    //alert("START REQUEST");
				  		           	that.processRequest(panels,index);
				  		           	// alert("Finish REQUEST");
				  		 }
        				if(i<panels.length)
        				{
        					//uncomment to test if the requested data were
        					// received 
        					 /*if(i == panels.length -1)
				  		           {
				  		           	 
				  		           	   for(j=0;j<panels.length;j++)
				  		           	   {
				  		           	   	     panels[j].printData();
				  		           	   }
				  		           }*/
        						var request =  Ext.Ajax.request(
								{
  									method: 'GET',
  									url: panels[i].geturl(),
  									timeout: 50000,
  									scope: that,
  									success: function(resp, opts)
  									{
  								   		//alert(resp.responseText);
  								   		panels[i].setData(resp.responseText);
				  		           		panels[i].setDataSet(i);
				  		           		//panels[i].printData();
				  		           
				  		           		getreqMethod(i+1);  
  									}
				  				});
        				}
        			}
                    i=0;
                    getreqMethod(i);  
        	}
        	//alert("FINISH REQUEST");
		};
       
       
        this.processRequest = function (panels,index)
        {
        	that.processRequestsStore(panels,index);				
        	if(currentpanel.length > 0)
		    {
		    	//alert("START HERE" + mainwindow);
		    	   if(mainwindow)
		    	   		mainwindow.hide();
		    	
                    for(j=0;j<currentpanel[currentpanel.length - 1].length;j++)
                			(currentpanel[currentpanel.length - 1][j]).hide();   
                //alert("START HERE" + mainwindow);
		    }
            var levyWindow = new LevyWindow();
           // alert("START HERE1" + mainwindow);
            gridsarray = that.createGrids(panels,index);  
            //alert("START HERE2" + mainwindow);
            levyWindow.addPanel(gridsarray,panels,index);
              //alert("START HERE3" + mainwindow);
          //alert("S= " + mainwindow + "  " + countpanels);
            
          mainwindow = new Ext.Panel({
						
								width : 1300,
								height :  950,
								layout: {
									type: 'fit',
    								align : 'stretch',
    								pack  : 'start'
								},
								items : [
                      				currentpanel[countpanels - 1]
								]
		 		    			
	    	    				});
	    	//alert("F= " + mainwindow);
            delete(gridsarray); 
            delete(levyWindow);
             //alert(" PROCESS FINISHED PAGE ");
        }
        this.processRequestsStore = function(panels,index)
        {
        	if(panels)
        	{
        	 	for (var i = 0;i < panels.length ;i++)
        			panels[i].processData();	
        	}
        }
        this.createGrids = function(panels,index)
        {
        	//alert("START CREATE GRIDS =" + panels + "  " + panels.length);
        	panelgrids = new Array();
        	if(panels)
        	{
        		
        		for (var i = 0;i < panels.length ;i++)
        		{
        		    //alert("PA = " + i + "   " + panels.length);
                    page = panels[i].getCurrentID();
                    storeData = panels[i].getstoreData();
                    title = panels[i].getTitle();
                   
        		    for(var j=0;j<page.length;j++)
        		    {
        		    	// alert("PA = " + j + "   " + page.length);
                    	if( page[j] == panels[i].getRootId())
                    	{
                    	      id = page[j];
                    	      getgrid = new WindowGrid();
           	 			      grid = getgrid.nextGrid(id,panels[i],index);
           	 			     // alert("grid = " + grid + " storedata = " + storeData);
            			      panelgrids.push(getgrid); 	
           	 			      delete(grid);
           	 			      delete(getgrid);
                    	}
        		    }
        		}
        	}
        	return panelgrids;
        }	
	}
	function LevyWindow()
	{
		var that = this;
		var p;
	    this.addPanel = function(grids,panels,index)
	    {
	    	
	    	   while(currentpanels.length!=0)
	    	   		currentpanels.pop();
	    	
	    	   currentpanel[countpanels] = new Array();
	    	    for(k=0;k<grids.length;k++)
	    	    {
	    	       	var currentgrids = grids[k].getGrids();
	    	       	
	    	        if( grids[k].getID() == 8 || grids[k].getID() == 5 || grids[k].getID() == 201 )
	    	        {
	    	        		var p = new Ext.Panel({
						
								width : grids[k].getwidth(),
								height :  grids[k].getheigth(),
								collapsible:  grids[k].getcollapsible(),
								//split:true,
			
								layout: {
									type: grids[k].getlayout(),
    								align : 'stretch',
    								pack  : 'start'
								},
								items : [
                      				currentgrids
								],
		 		    			tbar : [
					            		
									]
	    	    				}).render(Ext.getBody());
	    	    				currentpanels.push(p);
	    	    				currentpanel[countpanels].push(p);
	    	        }
	    	        else
	    	        {
	    	        	
	    	    		for(m=0;m<currentgrids.length;m++)
	    	    		
	    	    		{
	    	    			var p = new Ext.Panel({
						
							width : grids[k].getwidth(),
							height :  grids[k].getheigth(),
							collapsible:  grids[k].getcollapsible(),
			
							layout: {
								type: grids[k].getlayout(),
    							align : 'left',
    							pack  : 'start'
							},
							items : [
							   currentgrids[m]
							],
		 		    		tbar : [
					            		this.addbackbtn(m,k),
					            		this.addprintbtn(m,k,grids)
									]
	    	    			});
	    	    			p.render(Ext.getBody());
	    	    			
	    	    			currentpanels.push(p);
	    	    			currentpanel[countpanels].push(p);
	    	    		}	
	    	    
	    	        }
	    	    }
                countpanels++;
	    }
	    
	    this.addprintbtn = function(m,k,grids)
	    {
	    	button = new Ext.Button( {
                				//icon   : 'icons/back.png',
	    		                text : "PRINT",
                				height: 25,
                				width:  50,
                    
                				handler: function() 
                				{
                					   
                			 			Ext.ux.grid.Printer.print(grids);   
                				}
								})
								if(m==0 && k==0) 
								   button.show();
								else
								   button.hide();
	    	return button;
	    }
	    
	    this.addbackbtn = function(m,k)
	    {
								button = new Ext.Button( {
                				icon   : 'icons/back.png',
                				height: 25,
                				width:  50,
                    
                				handler: function() 
                				{
                    					if(currentpanel.length > 0)
                    					{
                    						mainwindow.hide();
                    						delete(mainwindow);
                    						for(var j=0;j<currentpanel[currentpanel.length - 1].length;j++)
                								(currentpanel[currentpanel.length - 1][j]).hide();
                    						currentpanel.pop();
                    						countpanels--;
                    						if(currentpanel.length >  0)
                    						{
                    							for( var j=0;j<currentpanel[currentpanel.length - 1].length;j++)
                									(currentpanel[currentpanel.length - 1][j]).show();
                									
                									 mainwindow = new Ext.Panel({
						
													width : 1300,
													height :  950,
													layout: {
																type: 'fit',
    															align : 'stretch',
    															pack  : 'start'
															},
															items : [
                      													currentpanel[countpanels-1]
																	],
		 		    												tbar : [
					            		
																			]
                									});
                    						}
                    						else
                    							start.initialize();
                    					}  
                				}
								})
								if(m==0 && k==0) 
								   button.show();
								else
								   button.hide();
	    	return button;
	    }
	}   
	
	
	 function   PanelURLRequestData() 
     {
     	this.paneltitle = "NONE";
        this.currentID = new Array();
        this.nextID = new Array();
        this.currentpath = -1;
        this.path = new Array();
        
    	this.pNames = new Array();
        this.pValues = new Array();  
        this.parValues = new Array();
        
        this.urladdress;
        this.datatext= null;
        this.dataset =0;
        this.store = new LevyStore();
        this.storeData = new Ext.data.ArrayStore();
        this.nextPtr = null;
        this.previousPtr = null;
        var that = this;
       
         this.setDataSet = function(d)
        {
        	this.dataset = d;
        }
        this.getDataSet = function()
        {
        	return this.dataset;
        }
        this.setNextPtr = function(ptr)
        {
        	this.nextPtr = ptr;
        }
         this.getNextPtr = function()
        {
        	return this.nextPtr;
        }
         this.setPreviousPtr = function(ptr)
        {
        	this.previousPtr = ptr;
        }
         this.getPreviousPtr = function()
        {
        	return this.previousPtr;
        }
        this.setcurrentPath = function(currentpath)
        {
        	 this.currentpath = currentpath;
        }
        this.setParameters = function(title,currentID,nextID,path,curpath)
        {
        	this.paneltitle = title;
        	this.currentID = currentID;
            this.nextID = nextID;
            this.path = path;
            this.currentpath = curpath;
        }
        this.getCurrentPathIndex = function()
        {
        	//alert("Current Path Index = " + this.currentpath);
        	return this.currentpath;
        }
        this.getPathArray = function()
        {
        	var s="";
        	for(i=0;i<this.path.length;i++)
        	{
        	   for(j=0;j<this.path[i].length;j++)
        	     s = s + " " + this.path[i][j] + "  ";
        	   s= s+ "\n";
        	}
        	//alert(s);
        	return this.path;
        }
        this.setTitle = function(title)
        {
        	this.paneltitle = title;
        }
        this.getTitle = function(title)
        {
        	//alert(this.paneltitle);
        	return this.paneltitle;
        }
        this.getCurrentID = function()
        {
        	//alert(that.currentID);
        	return that.currentID; 
        }
        this.setNextID = function(id)
        {
        	
        	this.nextID = id; 
        }
         this.setCurrentID = function(id)
        {
        	
        	this.currentID = id; 
        }
        this.getNextID = function()
        {
        	//alert(this.nextID);
        	return this.nextID; 
        }
        
        this.pushParameters = function(parValues)
        {
        	this.parValues.push(parValues);
        }
        this.popParameterts = function()
        {
        	this.parValues.pop();
        }
        this.getParameteres = function()
        {
        	return parValues;
        }
        this.pushValues = function(pValues)
        {
        
        	this.pValues.push(pValues);
        }
        this.popValues = function()
        {
        
        	this.pValues.pop();
        }
         this.pushNames = function(pNames)
        {
        	this.pNames.push(pNames);
        
        }
        this.popNames = function()
        {
        	this.pNames.pop();
        
        }
        this.getpNames = function()
        {
        	return this.pNames;
        }
        this.getpValues = function()
        {
        	return this.pValues;
        }
      
        this.seturl = function(urladdress)
        {
        	this.urladdress = urladdress;
        }
        this.geturl = function()
        {
        	return this.urladdress;
        }
        this.printURL = function()
        {
        	
        	alert(this.urladdress);
        }
       
        this.setData = function(datatext)
        {
        	//alert("setting data "  + datatext);
        	this.datatext = Ext.decode(datatext);
        	//this.printData();
        	//alert("data set");
        	
        }
        this.getData = function()
        {
        	
        	return this.datatext;
        
        	
        }
        this.printData = function()
        {
        	       var s= "";
        	       t = this.datatext.levy_data;
        	       s = s +  "Data Size  = " + t.data.length + "  " + t.id + " "  + t.root + "\n";
        	       
        	       for(var i=0;i<t.data.length;i++)
        	            s = s + " " + i + "   " + t.data[i] + "\n";
        	       alert(s);
        	            
        }
        this.printStore = function()
        {
        	
        	
        	var s= "";
        	s = s + "STORE LENGTH = " + this.store.data.length + " \n";
        	
        	for(i=0;i<this.store.data.length;i++)
        	{
        	      s = s + " " + this.store.getAt(i) + " \n";
        		 	 
        	}
            s = s + " Finish Printing Levy Store \n";
            alert(s);
        }
        this.printStoreData = function()
        {
        	var f=this.store.data.getAt(3);
        	var s="";
        	s = s + "Start Printing Store Data  = " + this.storeData.data.length + "\n";
           for(i=0;i<this.storeData.data.length;i++)
           {
           	       d= this.storeData.getAt(i);
           	       for(k=0;k<f.length;k++)
           	            s = s + f[k]  + "=" +  d.get(f[k])  + " ";
           	       s = s + "\n";
           	       
           }
           
        	alert(s + " FINISH Printing StoreDATA + \n");
        }
        this.processData = function()
        {
        	//alert("START prodata");
        	this.store.loadData(this.datatext.levy_data);
        	this.loadStoreData();
        	//alert("Finish prodata");
        }
        this.getData = function()
        {
        	return this.datatext;
        }
        this.getRootId = function()
        {
        	
        	return this.datatext.levy_data.id;
        	
        }
        this.setStore = function(sto)
        {
        	this.store = sto;
        }
        
        this.getStore = function()
        {
        	return this.store;
        }
        this.getstoreData = function()
        {
        	//that.printStoreData();
        	return this.storeData;
        }
        this.loadStoreData = function()
        {
        	 //alert("CASE Started = " + this.currentID);
        	 page = this.getCurrentID();
        	 
        	 //alert("Page length = " + page.length);
        	 id = -1;
        	 for(var a = 0; a < page.length; a++)
        	 {
        	 	//alert("page[a] =" + page[a] + "  " +  that.getRootId());
        	 	if(page[a] == that.getRootId())
        	 		id = page[a];
        	 }
        	 //alert("IDDDDD = " + id);
        	 switch(id)
        	 {
        	 	        ////////////////////////////////////////////
        	 	        // stores data for the query defined in claases.php
        	 	
        	 	        // stores data for the query defined in classes.php as $SearchData[0] = new StdClass();
						case 0:
					  			this.storeData =  new CaseStore();
						break;
						
						// stores data for the queries defined in classes.php as $SearchData[1] = new StdClass();
						// $SearchData[104] = new StdClass();, $SearchData[200] = new StdClass();
						case 1:
						case 104:
						case 200:
					  			this.storeData = new MasterReceiptStore();
						break;
						 // stores data for the query defined in classes.php as $SearchData[2] = new StdClass();
						case 2:
					  			this.storeData = new NameStore();
						break;
						// stores data for the query defined in classes.php as $SearchData[3] = new StdClass();,
						// $SearchData[105] = new StdClass();,
						case 3:
						case 105:
						       this.storeData = new AccountReceiptStore();
						break;
						// stores data for the queries defined in classes.php as $SearchData[4] = new StdClass();
						// $SearchData[7] = new StdClass();, $SearchData[101] = new StdClass();
						case 4:
						case 7:
						case 101:
						       this.storeData = new HistoryReceiptStore();
						break;
						// stores data for the queries defined in classes.php as $SearchData[5] = new StdClass();
						// $SearchData[8] = new StdClass();, $SearchData[201] = new StdClass();
						case 5:
						case 8:
						case 201:
						        this.storeData = new FinalReceiptStore();
						break;
						 // stores data for the query defined in classes.php as $SearchData[100] = new StdClass();
						case 100:
						        this.storeData = new NameCaseStore();
						break;	
        	}
        	
        	if(this.store.getAt(4))
        	     this.storeData.loadData(this.store.getAt(4)); 
        	
        		 
        }
        this.buidurl = function(urladdress,fieldValues,fieldNames)
		{
			if(fieldValues && fieldNames)
			{
				urlpostaddress = urladdress + '?';
				for(i=0;i<fieldValues.length-1;i++)
				{
		   			urlpostaddress = urlpostaddress + fieldNames[i] + '=' + fieldValues[i] + '&';
				}
				urlpostaddress = urlpostaddress + fieldNames[i] + '=' + fieldValues[i];
			}
			return urlpostaddress;
		}
        this.printNV = function(ind)
        {
        	for(i=0;i<this.pNames.length;i++)
        	   alert(ind + " = " + this.pNames[i] + " = " + this.pValues[i]);
        }
        
        
        this.clear = function()
        {
        	while(this.pNames.length > 0)
        	{
        		this.pNames.pop();
        		this.pValues.pop();
        	}
        	
        }
        
      
     }   
	
	Ext.define("Ext.ux.grid.Printer", {
 
    requires: 'Ext.XTemplate',
 
    statics: 
    {
        /**
         * Prints the passed grid. Reflects on the grid's column model to build a table, and fills it using the store
         * @param {Ext.grid.Panel} grid The grid to print
         */
        print: function(grids) {
            //We generate an XTemplate here by using 2 intermediary XTemplates - one to create the header,
            //the other to create the body (see the escaped {} below)
        	//open up a new printing window, write to it, print it and close
           var win = window.open('', 'printgrid');
         
            
        	 for(k=0;k<grids.length;k++)
              {
                	var currentgrids = grids[k].getGrids();
                	var title = grids[k].getWindowTitle();
                    var summary = grids[k].getSummaryData();
                  
                	for(m=0;m<currentgrids.length;m++)
                    {
                		var columns = currentgrids[m].columns;
 						//build a useable array of store data for the XTemplate
            			var data = [];
            			
            			
            			currentgrids[m].store.data.each(function(item)
            			{
                			var convertedData = [];
 
                			//apply renderers from column model
                			//var s = "";
                			for (var key in item.data) 
                			{
                    			var value = item.data[key];
                    			
 								Ext.each(columns, function(column)
 								{
                        				if (column.dataIndex == key) {
                                			convertedData[key] = column.renderer ? column.renderer(value) : value;
                                			//s = s + convertedData[key] + " ";
                        				}
                    			}, this);
                    			//s = s+ "\n";
                			}
                			//alert(s);
                		
 							data.push(convertedData );
 						
            			});
            			if(summary)
            			{
            				if(summary[m])
            				{
            					//alert(summary.length + "  " + m);
            					summary[m].data.each(function(item)
            					{
                					var convertedData = [];
 
                					//apply renderers from column model
                					var st = "";
                					for (var key in item.data) 
                					{
                    					var value = item.data[key];
                    			
 										Ext.each(columns, function(column)
 										{
                        						if (column.dataIndex == key) {
                                					convertedData[key] = column.renderer ? column.renderer(value) : value;
                                					st = st + convertedData[key] + " ";
                        						}
                       
                    					}, this);
                    					st = st+ "\n";
                					}
                					//alert(st);
                		
 									data.push(convertedData );
            				});
            				}
            			}
                    
            			var l =Ext.create('Ext.XTemplate', this.lineTpl).apply(title);
            			var tabletitle = Ext.create('Ext.XTemplate', this.tabletitleTpl).apply(currentgrids[m]);
            			var body     = Ext.create('Ext.XTemplate', this.bodyTpl).apply(columns);
            			var headings = Ext.create('Ext.XTemplate', this.headerTpl).apply(columns);
            			
 
            			var htmlMarkup = [
                				'<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">',
                				'<html>',
                  					'<head>',
                    					'<meta content="text/html; charset=UTF-8" http-equiv="Content-Type" />',
                    					'<link href="' + this.stylesheetPath + '" rel="stylesheet" type="text/css" media="screen,print" />',
                    					'<title>' + "  LEVY DATA  " + '</title>',
                 					 '</head>',
                  					'<body>',
                  					        l,
                   					 	'<table>', 
                   					 	    tabletitle ,
                   					 	    l,
                     					 	headings ,
                      						'<tpl for=".">',
                       					 		body,
                     				 		'</tpl>',
                    					'</table>',
                  					'</body>',
                				'</html>'
            				];
            			var html = Ext.create('Ext.XTemplate', htmlMarkup).apply(data);
            			
 						win.document.write(html);
 						
                    }
                   
              }
              if (this.printAutomatically){
                				win.print();
                				//win.close();
            			}
            			
              
        },
 
        /**
         * @property stylesheetPath
         * @type String
         * The path at which the print stylesheet can be found (defaults to 'ux/grid/gridPrinterCss/print.css')
         */
        stylesheetPath: '../../extjs/overview/resources/css/print.css',
 
        /**
         * @property printAutomatically
         * @type Boolean
         * True to open the print dialog automatically and close the window after printing. False to simply open the print version
         * of the grid (defaults to true)
         */
        printAutomatically: true,
 
        /**
         * @property headerTpl
         * @type {Object/Array} values
         * The markup used to create the headings row. By default this just uses <th> elements, override to provide your own
         */
         tabletitleTpl: [
                    '<h3>"                                                    {title}                                                                                               </h3>'                                                                                     ,     
        ],
        lineTpl: [
                    '<p>_______________________________________________________________________________________________________________________________________________________________________________________________</p>',     
        ],
        headerTpl: [
            '<tr>',
                '<tpl for=".">',
                    '<th>|{text}     </th>',
                '</tpl>',
            '</tr>'
        ],
 
        /**
         * @property bodyTpl
         * @type {Object/Array} values
         * The XTemplate used to create each row. This is used inside the 'print' function to build another XTemplate, to which the data
         * are then applied (see the escaped dataIndex attribute here - this ends up as "{dataIndex}")
         */
        bodyTpl: [
            '<tr>',
                '<tpl for=".">',
                    '<td>|{{dataIndex}}       </td>',
                '</tpl>',
            '</tr>'
        ],
         itemsTpl: [
            '<tr>',
                '<tpl for=".">',
                    '<td>|{text}     </td>',
                '</tpl>',
            '</tr>'
        ]
        
        
        
    }
    
    			 	
           
    
});








 	