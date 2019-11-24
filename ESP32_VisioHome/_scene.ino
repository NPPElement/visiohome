/*******************************************************************************
  Scene Control message
*******************************************************************************/
void SceneControl(int numscene) {  
  switch(numscene) {
    
    case 1:
    output[0] = 1;
    output[1] = 1;
    output[5] = 1;
  
      break;
      
    case 2:
    output[0] ^= 1;
    
      break;
      
    case 3:
    output[1] ^= 1;
    
      break;
      
    case 4:
    
      break;

    case 5:
    
      break;

    case 6:
    
      break;

    case 7:
  
      break;
      
    case 8:
    
      break;
      
    case 9:
    
      break;
      
    case 10:
    
      break;

    case 11:
    
      break;

    case 12:
    
      break;

    case 13:
    
      break;

    case 14:
    
      break;

    case 15:
    output[0] = 0;
    output[1] = 0;
    output[2] = 0;
    output[3] = 0;
    output[4] = 0;
    
      break;
      
    default:
    
      break;
  }
};
