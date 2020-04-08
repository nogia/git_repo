import pkg_resources
pkg_resources.require("matplotlib")
import matplotlib.pyplot as plt
import sys, ast
import numpy as np
def draw(list):
  	
  	print 'In Python: a set to', list
	plt.plot(list[0][0], list[1], 'ro')
	plt.axis(list[2][0])
	plt.show()
def drawSamples1(lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits
          
          if lists is not None and len(lists) > 0:
             figures = []
             subplots = []
             titles = ['Original','Corrected','Original And Correction Function','Corrected and Correction Function','Correction Function']
             for g in range(0,len(lists) ):
                 if g == 0 or g == 2 or g==4:
                   figures.append(0)
                   if g == 4:
                     subplots.append([3,1])
                   elif g == 0:
                     subplots.append([3,2])
                   else:
                     subplots.append([3,3])
                 else: 
                   figures.append(1)
                   if g == 3:
                     subplots.append([2,1])
                   else: 
                     subplots.append([2,2])
                
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
		                      print ' i =' ,i, ' Number Of Variable = ',len(list[1][i])
				      if len(list[1][i]) > 0:
				              print ' i =' ,i, ' Number Of Variable = ',len(list[1][i])
					      if len(list[0][0]) == len(list[1][i]):
                                                      plt.figure(g)
                                                      #plt.subplot(subplots[g][0],1,subplots[g][1])
                                                      if g < len(titles):
                                                      	plt.title(titles[g])
                                                      else:
                                                        plt.title(g)
                                                      plt.ylabel('Spectra')
                                                      plt.xlabel('Wavelength (nm)')

                                                      #plt.subplot(subplots[g])
						      plt.plot(list[0][0],list[1][i], linewidth=2.0)
                                                      plt.xlim([list[2][0][0],list[2][0][1]])
		                                      plt.ylim([list[2][0][2],list[2][0][3]])
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

#drawSamples1([   [ [ [1,2,3,4]  ],[[1,4,9,16],[3,10,13,10] ,[1,3,5,19],[5,5,5,5]],[[0, 6, 0, 20] ]],   [ [ [1,2,3,4]  ],[[1,4,9,16],[3,2,13,10] ,[1,17,5,19],[5,5,3,3]],[[0, 6, 0, 20] ]],   [ [ [1,2,3,4]  ],[[5,5,5,5]],[[0, 6, 0, 20] ]],    [ [ [1,2,3,4]  ],[[1,4,9,16],[3,2,13,10] ,[1,17,5,19],[5,5,5,5]],[[0, 6, 0, 20] ]] ,[ [ [1,2,3,4]  ],[[3,10,13,10] ,[5,5,5,5]],[[0, 6, 0, 20] ]] ])
#def drawSamples2(list):

#p = PlotObject(list)
#p.drawSamples(self,list)

class PlotObject: 
    def __init__(self): 
	self.list = [0,0,0,0]
        self.lists = [self.list,self.list,self.list]
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
        print 'In Python: method name = Show ', self.list
        #self.plt.show()
    def drawSamples(self,lists): #list[0][0] = valueOfX,list[1][i] = [samples][i],list[2][0] = xyLimits
          self.lists=lists
          print 'self.lists = ',self.lists
          if self.lists is not None and len(self.lists) > 0:
             figures = []
             subplots = []
             titles = ['Original','Corrected','Original And Correction Function','Corrected and Correction Function','Correction Function']
             for g in range(0,len(self.lists) ):
                 if g == 0 or g == 2 or g==4:
                   figures.append(0)
                   if g == 4:
                     subplots.append([3,1])
                   elif g == 0:
                     subplots.append([3,2])
                   else:
                     subplots.append([3,3])
                 else: 
                   figures.append(1)
                   if g == 3:
                     subplots.append([2,1])
                   else: 
                     subplots.append([2,2])
             for g in range(0,len(self.lists) ):
                  self.list = self.lists[g]
		  print 'list recieved from c++ =  ', self.list
		  if self.list is not None: 
		     if len(self.list) == 3: 
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
                                                      plt.figure(g)
                                                      #plt.subplot(subplots[g][0],1,subplots[g][1])
                                                      if g < len(titles):
                                                      	plt.title(titles[g])
                                                      else:
                                                        plt.title(g)
                                                      plt.ylabel('Spectra')
                                                      plt.xlabel('Wavelength (nm)')

                                                      # this will display g plots, each in seperate window
                                                      #plt.subplot(subplots[g])
						      plt.plot(self.list[0][0],self.list[1][i], linewidth=2.0)
						      plt.xlim([list[2][0][0],list[2][0][1]])
		                                      plt.ylim([list[2][0][2],list[2][0][3]])
		                                      #print 'list[1][i] = ' ,list[1][i],
		                                      #plt.show()
		                                      self.plt = plt
		               #self.plt.show()
		               
			    else:
			       print ' valueOfX = ',len(self.list[0]),' [samples] = ',len(self.list[1]),' xyLimits = ',len(self.list[2])

		               
		     else:
			  print 'List size = ' , len(self.list)
		  else:
		    print 'List = ',None
             self.plt.show()
	     return self.plt
             #print 'Finished'
