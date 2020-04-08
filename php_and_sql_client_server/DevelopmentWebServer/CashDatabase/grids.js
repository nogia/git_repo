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
    'PanelURLRequestData',
]);

	function WindowGrid()
	{
		this.grid = null;
	    this.storeData = null;
        this.windowtitle =null;
        this.summaryData = null;
        this.sumrecord = null;
        this.nID = null;
		this.request = new LevyRequest();
		this.windowIndex =-1;
		this.panel = null;
		this.index = -1;
		
		this.width=-1;
		this.height=-1;
		this.collapsible=false,
		this.layout=" ";
		var that = this;
	    var colcount=-1;
	    
	    
		this.getWindowTitle = function()
		{
			return this.windowtitle;
		}
		this.getID = function()
		{
		   return this.windowIndex;
		}
		this.getGrids = function()
		{
		   return this.grid;
		}
	    this.nextGrid =  function(windowIndex,panel,index)
	    {
	         this.storeData = panel.getstoreData();
	         panel.setTitle(WindowTitles[windowIndex]);
             this.windowtitle = panel.getTitle();
             this.nID = panel.getNextID();
             this.fNames = new Array();
     	     this.fValues = new Array();
     	     this.windowIndex = windowIndex;
			 this.panel = panel;
			 this.index = index;
			 this.grid = new Array();
            
	         
	       switch(windowIndex)
	       {
	      	 case 0:
	      	        this.width = 1200;
					this.height = 200;
					this.collapsible = true;
					this.layout = 'fit';
	         		this.grid.push (new Ext.grid.GridPanel(
	         		{
						store : this.storeData,
						title : this.windowtitle,
						
						columns : 
						[
								{
									header : 'case number',
									width : 549,
									dataIndex : 'casenum'
								},
								{
									header : 'levy number',
									width : 549,
									dataIndex : 'levy'
								},
								{
                					xtype: 'actioncolumn',
                					width: 100,
                					items: [{
                								header: 'Select Levy',
                    							icon   : 'icons/folder_go.gif' ,
                    							tooltip: 'Select Levy',
                    							handler: function(grid, rowIndex, colIndex) {
                        									that.createnextPage(that.storeData.getAt(rowIndex));
                    						    }
                					}]
                				}
				 		  ]
		        
	         		}
		    		));
		    	
		    	break;
		        case 2:
		         	   this.width = 1200;
					   this.height = 500;
					   this.collapsible = true;
					   this.layout = 'fit';
					   
		        	   this.grid.push (new Ext.grid.GridPanel(
		        	   	{
								store : this.storeData,
								title : this.windowtitle,
								columns : 
								[
										{
											header : 'Name',
											width : 365,
											dataIndex : 'name'
										},
										{
											header : 'Case Number',
											width : 365,
											dataIndex : 'casenum'
										},
										{
											header : 'levy Number',
											width : 365,
											dataIndex : 'levy'
										},
										{
                							xtype: 'actioncolumn',
                							width: 100,
                							items: [{
                									header: 'Select Receipt',
                    								icon   : 'icons/folder_go.gif',  // Use a URL in the icon config
                    								tooltip: 'Select Receipt',
                    								handler: function(grid, rowIndex, colIndex) {
                    	                					that.createnextPage(that.storeData.getAt(rowIndex));
                    								}
                							}]
           			 					}
								]
						}) );
				
		        break;
		        case 100:
		               this.width = 1200;
					   this.height = 300;
					   this.collapsible = true;
					   this.layout = 'fit';
		        	   this.grid.push(new Ext.grid.GridPanel(
		        	   	{
							store : this.storeData,
							title : this.windowtitle,
							columns : 
							[
			
									{
										header : 'levy Number',
										width : 365,
										dataIndex : 'levy'
									},
									{
										header : 'Case Number',
										width : 365,
										dataIndex : 'casenum'
									},
									{
										header : 'Name',
										width : 365,
										dataIndex : 'name'
									},
									{
                						xtype: 'actioncolumn',
                						width: 100,
                						items: [{
                								header: 'Select Receipt',
                    							icon   : 'icons/folder_go.gif',  // Use a URL in the icon config
                    							tooltip: 'Select Receipt',
                    							handler: function(grid, rowIndex, colIndex) {
                    	              
                    									that.createnextPage(that.storeData.getAt(rowIndex));
                    								}
                						}]
           			 				}
           
							]
						}));
						
		        break;
		       
		        case 4:
		        case 7:
		        case 101:
		           
		            this.width = 1200;
					this.height = 180;
					this.collapsible = false;
					this.layout = 'fit';
					this.summaryData = new Array();
					this.summaryData[0] = new Array();
					this.sumrecord = new Array();
					var temp = null;
					 if(that.storeData.data.length > 0)
		            {
		            	var temprec = that.storeData.getAt(0);
		         	    temp = temprec.get('receipt');
		            }
		            var groupingFeature = Ext.create('Ext.grid.feature.Grouping',{
        					groupHeaderTpl: 'Levy Number: {levy} ({rows.length} Item{[values.rows.length > 1 ? "s" : ""]})'
    				});
    				colcount=-1;
		            this.grid.push(new Ext.grid.GridPanel({
							store : this.storeData,
							title : this.windowtitle,
							collapsible: false,
							features: [{
						                  ftype: 'groupingsummary',
						                  groupHeaderTpl: 'Levy Number: {levy} ({rows.length} Item{[values.rows.length > 1 ? "s" : ""]})'
						    }],
		   					//width : 1560,
							height : 180,
		   					layout: {
					         	type: 'fit',
    				        	 align : 'left',
    				         	pack  : 'start'
				       		},
							columns : [
							{
								header : 'levy number',
								width : 196,
								dataIndex : 'levy',
								summaryType: 'count',
								 
								 summaryRenderer : function(value, summaryData, dataIndex) {
									return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"task",null);
								}
							},
							{
								header : 'receipt',
								width : 196,
								dataIndex : 'receipt',
								summaryRenderer : function(value, summaryData, dataIndex) {
									return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
								}
							},
								{
								header : 'valid',
								width : 196,
								dataIndex : 'valid',
								summaryRenderer : function(value, summaryData, dataIndex) {
									return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
								}
							},
								{
								header : 'fhs_date',
								width : 196,
								dataIndex : 'fhs_date',
								summaryType: 'max',
            					summaryRenderer : function(value, summaryData, dataIndex) {
									return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"number",null);
								}
							},
								{
								header : 'amount',
								width : 196,
								dataIndex : 'amount',
								summaryType: function(records){
                									var i = 0,
                    								length = records.length,
                    								total = 0,
                    								record;

                									for (; i < length; ++i) {
                    										record = records[i];
                    										total += record.get('amount');
               										 }
               										
                									return total;
								},
            				    summaryRenderer : function(value, summaryData, dataIndex) {
									return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"currency",null);
								}
							},
								{
								header : 'source',
								width : 90,
								dataIndex : 'source',
								summaryRenderer : function(value, summaryData, dataIndex) {
									return that.summaryRender(value, summaryData, dataIndex,++colcount,null,"end",new HistoryReceiptStore());
								}
							}
							]
						}));
		        break;
		        
		        case 5:
		        case 8:
		        case 201:
		         
		            	this.width = 1200;
						this.height = 250;
						this.collapsible = false;
						this.layout = 'accordion';
					
		           		// break each receipt into 2 different stores
		            		var s="";
		           		// alert("STORE LENGHT aaa= " + that.storeData.data.length);
		            		var receiptsArray = new Array();
		            		if(that.storeData.data.length > 0)
		            		{
		            			var temprec = that.storeData.getAt(0);
		         	   		 	var currentreceipt = temprec.get('recpt');
		         	    		var count=0;
		         	    		receiptsArray[count]= new Array();
		         	    
		         				for(i=0;i<that.storeData.data.length;i++)
		         				{
		         						//var nextrec = that.storeData.getAt(i);
		         						//var nextreceipt = temprec.get('recpt');
		         						if(currentreceipt != (that.storeData.getAt(i)).get('recpt'))
		         						{
		         							count++;
		         			    			receiptsArray[count]= new Array();
		         						}
		         			
		         			 			//alert(count + " " + currentreceipt);
		         			 			temprec = that.storeData.getAt(i);
		         			 			currentreceipt = temprec.get('recpt');
		         			 			receiptsArray[count].push(temprec);
		         				}
		         				count++;
		            			//s = s + " COUNT = " + (count) + "\n";
		            			var recdetailstoreArray = new Array();
		            			for(var x=0;x<count;x++)
		            			{
		            				var t = new FinalReceiptStore();
		            						t.loadData(receiptsArray[x]);
		            						recdetailstoreArray.push(t);
		            	
		            						for(j=0;j<t.data.length;j++)
		            						{
		            							var m = (t.getAt(j)).get('recpt');
		            							//alert("m= " + m);
		            						}
		            				};
		            			}
		         				  //alert("S = " + s);
		           	this.summaryData = new Array();
					this.sumrecord = new Array();
    			    creategridMethod = function (x,count,col)
		            {
		            	
		            	if(x<count)
		            	{
		            	  		var groupingFeature = new Array();
		                  
    					  		groupingFeature.push(Ext.create('Ext.grid.feature.Grouping',{
        						groupHeaderTpl: 'Receipts: {recpt} ({rows.length} Item{[values.rows.length > 1 ? "s" : ""]})'
    							}));
    							var receiptnumber = ""; 
    							temp = (recdetailstoreArray[x]).getAt(0);
    							if(temp)
    					   			receiptnumber = temp.get('recpt');
    							else
    					   		x= 1;
					        	that.summaryData[0] = new Array();
					    	    that.grid.push(new Ext.grid.GridPanel({
									store : recdetailstoreArray[x],
									title : that.windowtitle  + " " + receiptnumber,
							
		   							width : 1200,
									height : 130,
									
									features: [{
						                  ftype: 'groupingsummary',
						                  groupHeaderTpl: 'Receipts: {recpt} ({rows.length} Item{[values.rows.length > 1 ? "s" : ""]})'
						    		}],
					
		   							layout: {
					         		type: 'hbox',
    				         		align : 'stretch',
    				         		pack  : 'start'
				        			},
									columns : [
									{
										header : 'receipt',
										width : 125,
										dataIndex : 'recpt',
										summaryType: 'count',
										summaryRenderer : function(value, summaryData, dataIndex) {
											return that.summaryRender(value, summaryData, dataIndex,++col,temp,"task",null);
										}
									},
									{
										header : 'case number',
										width : 157,
										dataIndex : 'casenum',
										summaryType: 'max',		
            							summaryRenderer : function(value, summaryData, dataIndex) {
											return that.summaryRender(value, summaryData, dataIndex, ++col,temp,"number",null);
										}
									},
										{
										header : 'cout1',
										width : 75,
										dataIndex : 'count1',
										summaryType: 'count',
            							summaryRenderer : function(value, summaryData, dataIndex) {
											return that.summaryRender(value, summaryData, dataIndex, ++col,temp,"number",null);
										}
									},
										{
										header : 'scrn',
										width : 87,
										dataIndex : 'scrn',
										summaryRenderer : function(value, summaryData, dataIndex) {
											return that.summaryRender(value, summaryData, dataIndex,++col,null,null,null);
										}
									},
										{
										header : 'fund',
										width : 157,
										dataIndex : 'fund',
										summaryRenderer : function(value, summaryData, dataIndex) {
											return that.summaryRender(value, summaryData, dataIndex,++col,null,null,null);
										}
									},
										{
										header : 'objt',
										width : 157,
										dataIndex : 'objt',
										summaryRenderer : function(value, summaryData, dataIndex) {
											return that.summaryRender(value, summaryData, dataIndex,++col,null,null,null);
										}
									},
									{
										header : 'amount',
										width : 157,
										dataIndex : 'amount',
										summaryType: function(records){
                									var i = 0,
                    								length = records.length,
                    								total = 0,
                    								record;
                                                    for (; i < length; ++i) {
                    											record = records[i];
                    											total += record.get('amount');
               												 }
                                                    
                									return total;
										},
										summaryRenderer : function(value, summaryData, dataIndex) {
											
									         return that.summaryRender(value, summaryData, dataIndex,++col,temp,"currency",null);	
										}
									},	
									{
										header : 'dat_src',
										width : 157,
										dataIndex : 'dat_src',
										summaryRenderer : function(value, summaryData, dataIndex) {
											 
											return that.summaryRender(value, summaryData, dataIndex,++col,null,"end",new FinalReceiptStore());
									    }
									}	
									]
								}));
					
								creategridMethod(x + 1,count,-1);	
		            	}
		            }
		            var start=0;
		           
					creategridMethod(start,count,-1);
				
		        break;
		 
		       case 1:
		       case 104:
		       case 200:
		       		
		       		this.width = 1200;
					this.height = 100;
					this.collapsible = false;
					this.layout = 'fit';
					
		       		this.grid.push(new Ext.grid.GridPanel(
		       		{
		   				store : this.storeData,
		   				title : this.windowtitle,
		   				width : 1200,
						height : 75,
						collapsible: false,
		   				layout: {
					         type: 'fit',
    				         align : 'right',
    				         pack  : 'start'
				        },
						columns :
						[
								
									{
										header : 'case number',
										width : 90,
										dataIndex : 'casenum'
									},
									{
										header : 'count1',
										width : 67,
										dataIndex : 'count1'
									},
									{
										header : 'division',
										width : 70,
										dataIndex : 'division'
									},
									{
										header : 'agency',
										width : 70,
										dataIndex : 'agency'
									},
									{
										header : 'ref_no',
										width : 79,
										dataIndex : 'ref_no'
									},
									{
										header : 'levy number',
										width : 79,
										dataIndex : 'levy'
									},
									{
										header : 'outstanding_rcpt',
										width : 90,
										dataIndex : 'outstanding_rcpt'
									},
									{
										header : 'department',
										width : 74,
										dataIndex : 'department'
									},
							
									{
										header : 'tot_fin',
										width : 75,
										dataIndex : 'tot_fin'
									},
									{
										header : 'fin_pd',
										width : 79,
										dataIndex : 'fin_pd'
									},
									{
										header : 'fin_idx',
										width : 79,
										dataIndex : 'fin_idx'
									},
									{
										header : 'lev_stat',
										width : 79,
										dataIndex : 'lev_stat'
									},
									{
										header : 'disp_dt',
										width : 85,
										dataIndex : 'disp_dt'
									},
									{
										header : 'note_sent',
										width : 79,
										dataIndex : 'note_sent'
									},
									{
										header : 'source',
										width : 75,
										dataIndex : 'source'
									}
						]
		       		}));
					this.grid.push(new Ext.grid.GridPanel({
		   				store : this.storeData,
		   				title : this.windowtitle,
		   				width : 1200,
						height : 65,
						collapsible: false,
		   				layout: {
					         type: 'vbox',
    				         align : 'right',
    				         pack  : 'start'
				        },
						columns : 
						[
									{
										header : 'name',
										width : 158,
										dataIndex : 'name'
									},
									{
										header : 'addr1',
										width : 50,
										dataIndex : 'addr1'
									},
									{
										header : 'addr2',
										width : 50,
										dataIndex : 'addr2'
									},
									{
										header : 'payor',
										width : 208,
										dataIndex : 'payor'
									},
									{
										header : 'paddr1',
										width : 50,
										dataIndex : 'payor_addr1'
									},
									{
										header : 'paddr2',
										width : 50,
										dataIndex : 'payor_addr2'
									},
									{
										header : 'paddr3',
										width : 50,
										dataIndex : 'payor_addr3'
									},
									{
										header : 'pspn',
										width : 40,
										dataIndex : 'payor_spn'
									},
									{
										header : 'assess_dt',
										width : 210,
										dataIndex : 'assess_dt'
									},
									{
										header : 'status',
										width : 43,
										dataIndex : 'status'
									},
							
									{
										header : 'stat_dt',
										width : 260,
										dataIndex : 'stat_dt'
									}
					  ]
		       		}));
		       		break;
		       		
		       		case 3:
		       		case 105:
		       		
		       				this.width = 1200;
							this.height = 200;
							this.collapsible = false;
							this.layout = 'fit';
							this.summaryData = new Array();
							this.summaryData[0] = new Array();
							this.sumrecord = new Array();
					
							if(that.storeData.data.length > 0)
		           			 {
		            				var temprec = that.storeData.getAt(0);
		         	    			temp = temprec.get('levynum');
		            			}
		            		colcount = -1;
		       				this.grid.push(new Ext.grid.GridPanel(
		       				{
		   									store : this.storeData,
		   									title : this.windowtitle,
		   				
		   				 					features: [{
						                  					ftype: 'groupingsummary',
						                  					groupHeaderTpl: 'Receipts: {recpt} ({rows.length} Item{[values.rows.length > 1 ? "s" : ""]})'      
						    				}],
		   									collapsible: false,
		   									width : 1200,
											height : 200,
		   									layout: {
					         							type: 'fit',
    				         							align : 'left',
    				         							pack  : 'start'
				        							},
											columns : 
											[
													{
															header : 'case number',
															width : 100,
															dataIndex : 'casenum',
															summaryType: 'count',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"task",null);
															}
													},
													{
															header : 'count1',
															width : 84,
															dataIndex : 'count1',
															summaryType: 'count',
            												summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"number",null);
															}
													},
													{
															header : 'division',
															width : 84,
															dataIndex : 'division',
															summaryType: 'count',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'agency',
															width : 68,
															dataIndex : 'agency',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'levy number',
															width : 100,
															dataIndex : 'levynum',
															summaryType: 'max',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"number",null);
															}			
													},
													{
															header : 'arr_idx',
															width : 84,
															dataIndex : 'arr_idx',
															summaryType: 'count',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'screen',
															width : 84,
															dataIndex : 'screen',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'level',
															width : 84,
															dataIndex : 'level',
															summaryType: 'count',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'fund',
															width : 84,
															dataIndex : 'fund',
															summaryType: 'count',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'objt',
															width : 84,
															dataIndex : 'objt',
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,null,null,null);
															}
													},
													{
															header : 'org_amt',
															width : 84,
															dataIndex : 'org_amt',
								
															summaryType: function(records){
                																	var i = 0,
                    																length = records.length,
                    																total = 0,
                    																record;

                																	for (; i < length; ++i) {
                    																		record = records[i];
                    																		total += record.get('org_amt');
                																	}
                														return total;
															},
															summaryRenderer : function(value, summaryData, dataIndex) {
																					return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"currency",null);
															}
													},
													{
															header : 'new_amt',
															width : 84,
															dataIndex : 'new_amt',
															summaryType: function(records){
                																var i = 0,
                    															length = records.length,
                    															total = 0,
                    															record;

                																for (; i < length; ++i) {
                    																	record = records[i];
                    																	total += record.get('new_amt');
               										 							}
                														return total;
															},
															summaryRenderer : function(value, summaryData, dataIndex) {
																					return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"currency",null);
															}
													},
													{
															header : 'pd_amt',
															width : 84,
															dataIndex : 'pd_amt',
															summaryType: function(records){
                													var i = 0,
                    												length = records.length,
                    												total = 0,
                    												record;

                													for (; i < length; ++i) {
                    													record = records[i];
                    													total += record.get('pd_amt');
               										 				}
               										
                											return total;
															},
															summaryRenderer : function(value, summaryData, dataIndex) {
																				return that.summaryRender(value, summaryData, dataIndex,++colcount,temp,"currency",null);
															}
													},
													{
															header : 'source',
															width : 68,
															dataIndex : 'source',
															summaryType: 'count',
															summaryRenderer : function(value, summaryData, dataIndex) {
																					return that.summaryRender(value, summaryData, dataIndex,++colcount,null,"end",new AccountReceiptStore());
															}
													}
											]
		       				}
		       				));
		       		
		       		  break;
				      default : 
	                            alert("Window Does not exist");
	                  break;
	      } 
	      
	      return this.grid;
	      
	    }
	    this.getSummaryData = function()
	    {
	    	return this.summaryData;
	    }
	    this.getwidth = function()
	    {
	    	return this.width;
	    }
	    this.getheigth = function()
	    {
	    	return this.height;
	    }
	    this.getlayout = function()
	    {
	    	return this.layout;
	    }
	    this.getcollapsible = function()
	    {
	    	return this.collapsible;
	    }
	    this.createnextPage =  function(rec)
	    {
	    	 for(var i=0;i< that.nID.length;i++)
     	    {
     	           that.fNames[i] = new Array();
     	           that.fValues[i] = new Array();
     	                	      
     	          for(j=0;j<parameters[that.nID[i]][0].length;j++)
     	          {
     	               that.fNames[i][j] = parameters[that.nID[i]][0][j];
     	               that.fValues[i][j] = rec.get(parameters[that.nID[i]][1][j]);	
     	          }
     	    }
             cpath = that.panel.getPathArray();
	    	 curpath = that.panel.getCurrentPathIndex();
	    	 cID = new Array();
	    	 nID = new Array();
	    	 if(cpath[curpath + 1])
	    	     cID = cpath[curpath + 1];
	    	 
	    	 if(cpath[curpath + 2])
	    	     nID = cpath[curpath + 2];
	    	 
	    	 newpanel = new Array();
	       
	    	 // for(i = 0;i < fNames.length; i++)
	    				//for(j=0;j<fNames[i].length;j++)
	    	    					//alert("fNames[i][j] = " + fNames[i][j] + " "  + fValues[i][j]);
	    	 for(a=0; a < cID.length; a++)
              {
                   	   			p= new PanelURLRequestData();
                   	   	        p.setParameters(WindowTitles[cID[a]],cID,nID,   cpath,   that.panel.getCurrentPathIndex() + 1);
                   	   			for(j=0;j<that.fNames[a].length;j++)
                   	   			{
                   	   			 	//alert("fNames[i][j] = " + fNames[a][j] + " "  + fValues[a][j]);
                   	   		    	p.pushNames(that.fNames[a][j]);
                   	   	            p.pushValues(that.fValues[a][j]);
                   	   			}
                   	   			 
                   	   			url = p.buidurl(  phpurl, p.getpValues() , p.getpNames() );
                   	   			//alert("Build Url= " + url);
                   	   		 	p.seturl(url);
                   	   		 	newpanel.push(p); 
                   	  		    delete(p);
   	 
              }
             that.panel.setNextPtr(newpanel); 	  
            // that.request.testRequest(panel.getNextPtr(),index);
             that.request.postRequest(that.panel.getNextPtr(),that.index);
             that.request.getRequest(that.panel.getNextPtr(),that.index);
	    }
	    
	    this.summaryRender = function(value, summaryData, dataIndex,colcount,temp,formattype,storedata)
	    {
       								   var tempdata = '';
								 	   
								 	   if(temp)
								 	   {
								 	   	   if(formattype == "task")
								 	   	   {
								 	   	    	tempdata = ((value === 0 || value > 1) ? '(' + value + ' Tasks)' : '(1 Task)');
								 	   	   }
								 	   	   else if(formattype == "number")
								 	   	   {
								 	   	         tempdata = value;
								 	   	   }
								 	   	   else if(formattype == "currency")
								 	   	   {
								 	   	        tempdata = Ext.util.Format.usMoney(value); 
								 	   	   }
								 	   }
								 	  that.summaryData[0][colcount] = tempdata;
								 	 
								 	  if(formattype == "end"  )
								 	   {
								 	     var ttemp = [];
								 	     ttemp.push(that.summaryData[0]);
					                     storedata.loadData(ttemp);
					                     //alert("Summary Length = " + storedata.data.length);
								 	     /*for(var i=0;i<storedata.data.length ;i++)
								 	     	{
								 	         			var t = storedata.getAt(i);
								 	         			if(t.get('amount'))
								 	        			 	alert("AMOUNT = " + t.get('amount') + "i= " + i );
								 	     	}*/
					                     that.sumrecord.push(storedata);
								 	    /*alert("Summary Length111 = " + that.sumrecord.length);
								 	     	for(var i=0;i<that.sumrecord.length ;i++)
								 	     	{
								 	     		alert("Len222=" + i + " " + that.sumrecord[i].data.length);
								 	       		for(var j=0;j<that.sumrecord[i].data.length ;j++)
								 	       		{
								 	         			var t = that.sumrecord[i].getAt(j);
								 	         			if(t.get('amount'))
								 	        			 	alert("AMOUNT = " + t.get('amount') + "i= " + i + " j  = " + j);
								 	       		}
								 	     	}*/
								 	   }
                                       return tempdata;
	    }
	    this.getSummaryData = function()
	    {
	    	return this.sumrecord;
	    }
	    
	}
	   
	
	
	
		
		
	