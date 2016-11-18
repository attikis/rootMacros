{
  // Create object
  TRandom RndmNumGenerator;

  //  Note: RndmNumGenerator.Integer(Max-1); , where max is the maximum int you want to generate random numbers. The min by default is zero.
  Int_t myInt = -1;
  
  // Loop and test that it does what you want it to do.
  for( Int_t i = 0; i < 100; i++){
    myInt = RndmNumGenerator.Integer(2); 
  std::cout << "myInt = " << myInt << std::endl;
  }

}
