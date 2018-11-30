import junit.framework.TestCase;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
	public void testManualTest(){
		//You can use this function to implement your manual testing   
		UrlValidator urlVal = new UrlValidator();

		// List of strings to test, taken from the tabs open in my web browser.
		int numtests = 20;
		String tests[] = new String[] {
					"https://www.google.com/",
					"https://mail.google.com/mail/u/1/?zx=4hfnoeq6lana#inbox",
					"https://mail.google.com/mail/b/ANR_UvS-oEJfNneriZARTivUbDzNwlwG7NJLfWBVkgsAZ_XZwsq8/u/0/#starred",
					"https://forum.ss13polaris.com/index.php",
					"https://github.com/PolarisSS13/Polaris/pulls",
					"http://www.astronomy.com/news",
					"https://imgur.com/a/tGhH4",
					"https://www5.whentowork.com/cgi-bin/w2wE.dll/empmessaging.htm?SID=139824062427F&Show=New",
					"http://www.byond.com/docs/ref/",
					"https://ffxiv.consolegameswiki.com/wiki/Garo",
					"http://en.ff14housing.com/itemlist.php?h=4",
					"https://ffxiv.gamerescape.com/wiki/Behemoth_Horn",
					"https://docs.google.com/document/d/1V6yCb_7q7ueehxElurCIUT1Ooudv8s_dZptJ6xvZGjY/edit#heading=h.2qtbycupymke",
					"http://web.engr.oregonstate.edu/~benl/Courses/ece375.fa18/Assignments/hw4_ece375_fa18.pdf",
					"https://stackoverflow.com/questions/14736343/java-array-declaration-in-multiple-lines",
					"https://se2-finalproject.slack.com/messages/CDY6G24QP/?",
					"https://oregonstate.instructure.com/courses/1692917/assignments/7334042",
					"https://github.com/cs362-004/CS362-004-F2018",
					"https://www.youtube.com/watch?v=7z4WJAEG3u8",
					"https://docs.oracle.com/javase/7/docs/api/java/lang/String.html"
		};
		boolean expected_out[] = new boolean[20];
		// Generate the expected outcomes for each test case
		for(int i = 0; i < numtests; i++)
			expected_out[i] = true; // All URLs are definitely valid, they're taken from working webpages

		// Run all tests and output false test cases
		for(int i = 0; i < numtests; i++){
			boolean out = urlVal.isValid(tests[i]);
			//assertEquals(expected_out[i], out);
			if(out != expected_out[i])
				System.out.println("Incorrect operation: `" +  tests[i] + "` expected " + (expected_out[i] ? "TRUE" : "FALSE") + ", but found " + (out ? "TRUE" : "FALSE"));
		}
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
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
