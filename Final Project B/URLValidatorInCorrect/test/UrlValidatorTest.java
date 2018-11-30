import junit.framework.TestCase;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
      //Testing schemes
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      int totalTest = 0;
      int validTest = 0;


      Pair[] testUrlScheme = {new Pair("ftp://", true),
              new Pair("https://", true),
              new Pair("h3t://", true)};
              //new Pair("http:/", false),
             // new Pair("hp//", false),
             // new Pair("://", false)};


      Pair[] testUrlAuthority = {new Pair("www.google.com", true),
              new Pair("google.com", true),
              new Pair("255.255.255.255", true),
              new Pair("0.0.0.0", true)};
             // new Pair("286.256.265.295", false),
             // new Pair("2.1.3.4.6", false),
             // new Pair("abc.", false),
             // new Pair("sdv", false)};


      Pair[] testUrlPort = {new Pair("", true),
              new Pair(":80", true),
              new Pair(":65535", true),
              new Pair(":0", true)};
             // new Pair(":68535", false),
             // new Pair(":-1", false),
              //new Pair(":68abc", false)};


      Pair[] testUrlPath = {new Pair("", true),
              new Pair("/~test1", true),
              new Pair("/abc/123", true),
              new Pair("/$abc", true)};
              //new Pair("/../", false),
              //new Pair("/test1//abc", false),
              //new Pair("//#/test", false)};

     Pair[] testList = new Pair[5000];

      for (int idScheme = 0; idScheme < testUrlScheme.length; ++idScheme)
      {

         for (int idAuth = 0; idAuth < testUrlAuthority.length; ++idAuth)
         {
            for (int idPort = 0; idPort < testUrlPort.length; ++idPort)
            {
               for (int idPath = 0; idPath < testUrlPath.length; ++idPath)
               {
                  String temp = testUrlScheme[idScheme].item;
                          temp = temp + testUrlAuthority[idAuth].item;
                          temp = temp + testUrlPort[idPort].item;
                          temp = temp + testUrlPath[idPath].item;

                  if(testUrlScheme[idScheme].valid == true
                          && testUrlAuthority[idAuth].valid == true
                          && testUrlPort[idPort].valid == true
                          && testUrlPath[idPath].valid == true) {

                      testList[totalTest] = new Pair(temp, true);
                     validTest++;
                  }
                  else
                  {
                     testList[totalTest] = new Pair(temp, false);
                  }

                  totalTest++;
               }
            }
         }
      }

      for (int idx = 0; idx < totalTest; idx++)
      {
          try {
              Boolean test = urlVal.isValid(testList[idx].item);
              Boolean known = testList[idx].valid;
              assertEquals(testList[idx].item, known, test);
          } catch(Error e)
          {
              System.out.print("Error: ");
              System.out.println(e);
          }
      }
   }
   
   public void testYourSecondPartition(){

   }
   //You need to create more test cases for your Partitions if you need to
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
