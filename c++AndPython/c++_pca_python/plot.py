import pkg_resources
pkg_resources.require("matplotlib")
import matplotlib.pyplot as plt
import sys, ast
import numpy as np
import textwrap
def draw(list):
  	
  	print 'In Python: a set to', list
	plt.plot(list[0][0], list[1], 'ro')
	plt.axis(list[2][0])
	plt.show()

def drawSamples2(lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits

     f, axarr = plt.subplots(len(lists) + 1 ,1) 
     for g in range(0,len(lists) ):
        list = lists[g]
        axarr[g].plot(list[0][0],list[1][0],marker='p',linestyle='-',linewidth=2.0,color='m') 
        axarr[g].set_title('Axis [0,0]')
        axarr[g].set_ylabel('Spectra')
        axarr[g].set_xlabel('Wavelength (nm)')
        axarr[g].set_xlim([list[2][0][0],list[2][0][1]])
        axarr[g].set_ylim([list[2][0][2],list[2][0][3]])
     plt.show()

#drawSamples2([   [ [ [1,2,3,4]  ],[[1,4,9,16],[3,10,13,10] ,[1,3,5,19],[5,5,5,5]],[[0, 6, 0, 20] ]]   ])   

def drawSamples1(lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits
          
          if lists is not None and len(lists) > 0:
             figures = []
             subplots = []
             titles = ['Original','Corrected','Original And Correction Function','Corrected and Correction Function','Correction Function']
             for g in range(0,len(lists) ):
                  if g==0:
                     figures.append(0)
                     subplots.append([1,1])
                  elif g == 2 or g == 4:
                    figures.append(1)
                    if g == 2:
                      subplots.append([2,1])
                    #elif g == 0:
                     #subplots.append([3,2])
                    else:
                      subplots.append([2,2])
                  else: 
                   figures.append(2)
                   if g == 3:
                     subplots.append([2,1])
                   else: 
                     subplots.append([2,2])
             list = lists[0]
             f, axarr = plt.subplots(len(lists)) 
             axarr[0].plot(list[0][0],list[1][0]) 
             axarr[0].set_title('Axis [0,0]')
             
             for g in range(0,len(lists) ):
                  list = lists[g]
                
                  print 'list recieved from input =  ', list, ' g = ',g
		  if list is not None: 
		     if len(list) == 3: 
		       if list[0] is not None and list[1] is not None and list[2] is not None:
		         print 'List0 = ',None
		         if list[0][0] is not None and list[1][0] is not None and list[2][0] is not None:
		            print 'len(list[0][0]) = ',len(list[0][0]),' len(list[1][0] = ' ,len(list[1][0]),' len(list[2][0]=',len(list[2][0])
		            if len(list[0][0]) > 0 and len(list[1][0]) > 0 and len(list[2][0]) == 4:
			       print 'Number Of Samples = ' ,len(list[1]) 
			       for i in range(0,len(list[1]) ):
		                      #print ' i =' ,i, ' Number Of Variable = ',len(list[1][i])
				      if len(list[1][i]) > 0:
				              #print ' i =' ,i, ' Number Of Variable = ',len(list[1][i])
					      if len(list[0][0]) == len(list[1][i]):
                                                      fig = plt.figure(figures[g])
                                                      plt.subplot(subplots[g][0],1,subplots[g][1])
                                                      if g < len(titles):
                                                      	#plt.title(titles[g])
                                                        l = [197.52, 207.97, 212.45, 214.83, 218.11, 245.73, 246.32, 255.79, 266.43, 267.31, 272.91, 280.86, 282.04, 286.74, 287.92, 290.86, 291.44, 292.32, 310.2, 312.83, 314.29, 323.63, 329.74, 334.11, 341.09, 341.67, 343.12, 349.21, 351.53, 361.08, 366.57, 368.01, 374.35, 377.81, 394.48, 412.21, 417.63, 419.63, 439.24, 446.88, 450.27, 456.77, 459.59, 467.75, 471.13, 471.41, 484.3, 485.42, 489.9, 499.66]
                                                        my_list0 = ",".join(str(i) for i in l) 
							my_list = '[' + my_list0 + ']'
                                                      
                                                        #print my_list
                                                        plt.title("\n".join(textwrap.wrap(my_list,80)),fontsize = 6)
                                                      else:
                                                        plt.title(g)
                                                      plt.ylabel('Spectra')
                                                      plt.xlabel('Wavelength (nm)')
                                                      plt.plot(list[0][0],list[1][i], marker='p',linestyle='-',linewidth=2.0,color='m')
                                                      plt.xlim([list[2][0][0],list[2][0][1]])
		                                      plt.ylim([list[2][0][2],list[2][0][3]])


                                                      #plt.subplot(subplots[g])
                                                      #plt.figure(len(lists))
		                                      #plt.subplot(len(self.lists),1,g + 1)
                                                      #axarr[0, 0].plot(list[0][0],list[1][i])
						     
		                                      #print 'list[1][i] = ' ,list[1][i],
		                                      #plt.show()
		               #plt.show()
				     
			    else:
				 print ' valueOfX = ',len(list[0]),' [samples] = ',len(list[1]),' xyLimits = ',len(list[2])
		            #plt.show()
		               
		     else:
			  print 'List size = ' , len(list)
		  else:
		    print 'List = ',None
             plt.show()

#drawSamples2([   [ [ [1,2,3,4]  ],[[1,4,9,16],[3,10,13,10] ,[1,3,5,19],[5,5,5,5]],[[0, 6, 0, 20] ]],   [ [ [1,2,3,4]  ],[[1,4,9,16],[3,2,13,10] ,[1,17,5,19],[5,5,3,3]],[[0, 6, 0, 20] ]],   [ [ [1,2,3,4]  ],[[5,5,5,5]],[[0, 6, 0, 20] ]],    [ [ [1,2,3,4]  ],[[1,4,9,16],[3,2,13,10] ,[1,17,5,19],[5,5,5,5]],[[0, 6, 0, 20] ]] ,[ [ [1,2,3,4]  ],[[3,10,13,10] ,[5,5,5,5]],[[0, 6, 0, 20] ]] ])



class PlotObject: 
    def __init__(self): 
	self.list = [0,0,0,0]
        self.lists = [self.list,self.list,self.list,self.list]
        self.plt = None
    	print 'In Python: instance created ', self.list
    def draw(self,list):
  	self.list=list
  	print 'In Python: a set to', self.list
	plt.plot(self.list[0][0], self.list[1][0], 'ro')
	plt.axis(self.list[2][0])
	plt.show()
    def draw1(self,list):
         self.list=list
         print 'list recieved from c++ =  ', self.list
    def ShowSamples(self,list):
        self.list=list
        print 'In Python: method name = Show ', self.list[4]
        #self.plt.show()
    def drawFilteredSPectra1(self,lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits, list[3][0] = 
          self.lists=lists
          #print 'self.lists = ',self.lists
          if self.lists is not None and len(self.lists) > 0:
             figures = []
             subplots = []
           
             for g in range(0,len(self.lists) ):
                 figures.append(g)
             print 'len(self.lists)=',len(self.lists)  
             plt.figure(len(self.lists) - 1)
             if len(self.lists) == 1:
                length = len(self.lists) 
             else:
                length = len(self.lists)
             f, axarr = plt.subplots(1,1) 
             plt.subplots_adjust(hspace = 0.5)  
          plt.show() 
    def drawFilteredSPectra(self,lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits, list[3][0] = 
          self.lists=lists
          #print 'self.lists = ',self.lists
          if self.lists is not None and len(self.lists) > 0:
             figures = []
             subplots = []
           
             for g in range(0,len(self.lists) ):
                 figures.append(g)
             #print 'len(self.lists)=',len(self.lists)  
             plt.figure(len(self.lists) - 1)
             if len(self.lists) == 1:
                length = len(self.lists) + 1
             else:
                length = len(self.lists)
             f, axarr = plt.subplots(length,1) 
             plt.subplots_adjust(hspace = 0.5)   
             for g in range(0,len(self.lists) ):
                
                 
                  self.list = self.lists[g]
                 
                  tuplen = len(self.list[3][g])
                  #print 'tuplelen = ',tuplen
                  #for a in range(0,tuplen):
                    #print "a=",a ,' ',self.list[3][g][a]
		  #print 'list recieved from c++ =  ', self.list
		  if self.list is not None: 
		     if len(self.list) == 4: 
		       if self.list[0] is not None and self.list[1] is not None and self.list[2] is not None:
		         #print 'len(self.list[0][0]) = ',len(self.list[0][0]),' len(list[1][0] = ' ,len(self.list[1][0]),' len(list[2][0]=',len(self.list[2][0])
		         if self.list[0][0] is not None and self.list[1][0] is not None and self.list[2][0] is not None:
		            #print 'list[0][0] = ',len(self.list[0][0]),' list[1][0] = ' ,len(self.list[1][0]),' list[2][0]=',len(self.list[2][0])
		            if len(self.list[0][0]) > 0 and len(self.list[1][0]) > 0 and len(self.list[2][0]) == 4:
		               #print 'Number Of Samples = ' ,len(self.list[1]) 
			       for i in range(0,len(self.list[1]) ):
		                      #print ' i =' ,i, ' Number Of Variable = ',len(self.list[1][i])
				      if len(self.list[1][i]) > 0:
                                              #print ' i =' ,i, ' Number Of Variable = ',len(self.list[1][i])
					      if len(self.list[0][0]) == len(self.list[1][i]):
                                                     
                                                      fig = plt.figure(figures[g])
                                                     
                                                      if len(self.list[3]) > 0 and len(self.list[3][g]) > 0:
                                                        
                                                        fig.suptitle([self.list[3][g][2][0],self.list[3][g][2][1],self.list[3][g][0]],fontsize=12)
                                                        my_title00 = "".join(str(i) for i in self.list[3][g][2][0])
                                                        my_title01 = "".join(str(i) for i in self.list[3][g][2][1])
                                                        my_title02 = "\n".join(textwrap.wrap('[' + ",".join(str(i) for i in self.list[3][g][0])  + ']',80))
						        my_title03 = "\n".join(textwrap.wrap('[' + ",".join(str(i) for i in self.list[3][g][1])  + ']',80))
                                                        my_tytle0 = my_title00 + my_title01 + my_title02 + my_title03
                                                        plt.title(my_tytle0,fontsize=6)
                                                        #plt.title("\n".join(textwrap.wrap('[' + ",".join(str(i) for i in self.list[3][g][1])  + ']',80)),fontsize = 6)
                                                        plt.ylabel(self.list[3][g][2][3])
                                                      	plt.xlabel(self.list[3][g][2][2])
                                                      else:
                                                        print 'len(self.list[3]) = ',len(self.list[3]),'  len(self.list[3][g]=',len(self.list[3][g])
                                                      
                                                     
                                                      if len(self.list[3][g][2]) >= 5:
                                                        if self.list[3][g][2][4] == 'p':
                                                          plt.plot(self.list[0][0],self.list[1][i], marker='p',linestyle='-',linewidth=1.0)
                                                          
                                                      else:
                                                        plt.plot(self.list[0][0],self.list[1][i], marker='.',linestyle='-',linewidth=1.0)
                                                       
                                                    
						      plt.xlim([self.list[2][0][0],self.list[2][0][1]])
		                                      plt.ylim([self.list[2][0][2],self.list[2][0][3]])
                                                     
                                                      if len(self.lists) > 0 and len(self.list[3]) > 0 and len(self.list[3][g]) > 0:
                                                       
                                                        if len(self.list[3][g][2]) >= 5: 
                                                          if self.list[3][g][2][4] == 'p':
                                                             axarr[g].plot(self.list[0][0],self.list[1][i],marker='p',linestyle='-',linewidth=0.5) 
                                                        else:
                                                           axarr[g].plot(self.list[0][0],self.list[1][i],marker='.',linestyle='-',linewidth=1.0) 
                                                           
                                                        my_title00 = "".join(str(i) for i in self.list[3][g][2][0])
                                                        my_title01 = "".join(str(i) for i in self.list[3][g][2][1])
                                                        #my_title02 = "".join(str(i) for i in self.list[3][g][0])
                                                        my_title02 = "\n".join(textwrap.wrap('[' + ",".join(str(i) for i in self.list[3][g][0])  + ']',80))
						        my_title03 = "\n".join(textwrap.wrap('[' + ",".join(str(i) for i in self.list[3][g][1])  + ']',80))
                                                        my_tytle0 = my_title00 + my_title01 + my_title02 + my_title03
                                                       
                                                        axarr[g].set_title(my_tytle0,fontsize=8)
						        axarr[g].set_ylabel(self.list[3][g][2][3],fontsize=8)
							axarr[g].set_xlabel(self.list[3][g][2][2],fontsize=8)
							axarr[g].set_xlim([self.list[2][0][0],self.list[2][0][1]])
							axarr[g].set_ylim([self.list[2][0][2],self.list[2][0][3]])
                                                      else:
                                                       
                                                        print 'len(self.list[3]) = ',len(self.list[3]),'  len(self.list[3][g] = ',len(self.list[3][g])
                                                    
                                                                      
		               #self.plt.show() 
			    else:
			       print ' valueOfX = ',len(self.list[0]),' [samples] = ',len(self.list[1]),' xyLimits = ',len(self.list[2])
  
		     else:
			  print 'List size = ' , len(self.list)
		  else:
		    print 'List = ',None
             print 'Number Of Graphs =', len(self.lists)
            
             plt.show()
	     return self.plt
             
    def drawSamples(self,lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits
          self.lists=lists
          #print 'Lists Passed from C++ Titles = 0 ',self.lists
       
          if self.lists is not None and len(self.lists) > 0:
             figures = []
             subplots = []
             titles = ['Original','Corrected','Original And Correction Function','Corrected and Correction Function','Correction Function']
             for g in range(0,len(self.lists) ):
                 if g==0:
                     figures.append(0)
                     subplots.append([1,1])
                 elif g == 2 or g == 3 or g == 4:
                   figures.append(1)
                   if g == 4:
                     subplots.append([3,1])
                   elif g == 2:
                     subplots.append([3,2])
                   else:
                     subplots.append([3,3])
                 else: 
                   figures.append(2)
                   subplots.append([1,1])
                   #if g == 3:
                     #subplots.append([2,1])
                   #else: 
                     #subplots.append([2,2])
                
             print 'len(self.lists)=',len(self.lists)  
             #for g in range(0,len(self.lists) ):
             for g in range(0,len(self.lists) ):
                  #print 'g=',g
                  self.list = self.lists[g]
		  #print 'list recieved from c++ =  ', self.list
		  if self.list is not None: 
		     if len(self.list) == 4: 
		       if self.list[0] is not None and self.list[1] is not None and self.list[2] is not None:
		         #print 'len(self.list[0][0]) = ',len(self.list[0][0]),' len(list[1][0] = ' ,len(self.list[1][0]),' len(list[2][0]=',len(self.list[2][0])
		         if self.list[0][0] is not None and self.list[1][0] is not None and self.list[2][0] is not None:
		            #print 'list[0][0] = ',len(self.list[0][0]),' list[1][0] = ' ,len(self.list[1][0]),' list[2][0]=',len(self.list[2][0])
		            if len(self.list[0][0]) > 0 and len(self.list[1][0]) > 0 and len(self.list[2][0]) == 4:
		               #print 'Number Of Samples = ' ,len(self.list[1]) 
			       for i in range(0,len(self.list[1]) ):
		                      #print ' i =' ,i, ' Number Of Variable = ',len(self.list[1][i])
				      if len(self.list[1][i]) > 0:
				              #print ' i =' ,i, ' Number Of Variable = ',len(self.list[1][i])
                                              #print 'Title data = 0',self.list[3][0]
                                              #print 'Title data = 1',self.list[3][1]
                                              #print 'Title data = 2',self.list[3][2]
                                              #print 'Title data = 2',self.list[3][3]
					      if len(self.list[0][0]) == len(self.list[1][i]):
                                                      plt.figure(figures[g])
                                                      plt.subplot(subplots[g][0],1,subplots[g][1])
                                                      if g < len(titles):
                                                      	plt.title(titles[g])
                                                      else:
                                                        plt.title(g)
                                                      plt.ylabel('Spectra')
                                                      plt.xlabel('Wavelength (nm)')
                                                     
                                                      if titles[g] == 'Correction Function' or titles[g] == 'Original And Correction Function' or titles[g] == 'Corrected and Correction Function':
                                                         #print 'i=',i,'  self.list[1] = ',self.list[1]
                                                         #plt.plot(list[0][0],list[1][i], marker='p',linestyle='-',linewidth=3.0,color='m')
                                                         if i == len(self.list[1]) - 1:
                                                            plt.plot(self.list[0][0],self.list[1][i], marker='.',linestyle='-',linewidth=1.0,color='m')
                                                         else:
                                                            plt.plot(self.list[0][0],self.list[1][i], marker='.',linestyle='-',linewidth=1.0)
                                                      else:
						         plt.plot(self.list[0][0],self.list[1][i], marker='.',linestyle='-',linewidth=1.0)
                                                      plt.subplots_adjust(hspace = 0.5)
						      plt.xlim([self.list[2][0][0],self.list[2][0][1]])
		                                      plt.ylim([self.list[2][0][2],self.list[2][0][3]])
		                                      #self.plt = plt
                                                     
                                                      
		               #self.plt.show()
		               
			    else:
			       print ' valueOfX = ',len(self.list[0]),' [samples] = ',len(self.list[1]),' xyLimits = ',len(self.list[2])
  
		     else:
			  print 'List size = ' , len(self.list)
		  else:
		    print 'List = ',None
             print 'Number Of Graphs =', len(self.lists)
             plt.show()
	     return self.plt
             
