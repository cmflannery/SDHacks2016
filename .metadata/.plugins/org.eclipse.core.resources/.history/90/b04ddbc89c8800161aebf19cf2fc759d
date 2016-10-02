import com.docusign.esign.api.*;
import com.docusign.esign.client.*;
import com.docusign.esign.model.*;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import java.io.FileOutputStream;
import java.awt.Desktop;

import java.util.List;
import java.util.ArrayList;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.util.Base64;
import java.util.HashSet;
import java.util.Set;

import java.net.URI;

import javafx.application.Application;
import javafx.scene.layout.*;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.StackPane; 
import javafx.scene.Scene; 
import javafx.scene.text.Text;



public class main extends Application implements EventHandler <ActionEvent> {
	
        boolean gate1 = false;
        boolean gate2 = false;
        boolean gate3 = false;
        
        Button button1;
        Button button2; 
        Button button3; 
	 public static final String UserName = "cameron.m.flannery@gmail.com";
	 public static final String Password = "sdhacks2016";
	 public static final String IntegratorKey = "bac3326a-8237-4648-aac9-e055ab2cf7c7";

	 
	 public static final String BaseUrl = "https://demo.docusign.net/restapi";
	    //public static final String BaseUrl = "http://dsv010331a/restapi";
	    
	 public static final String SignTest1File = "/src/test//docs/SignTest1.pdf";
	 public static final String TemplateId = "[TEMPLATE_ID]";
	 public static String EnvelopeId = "[ENVELOPE_ID]"; // JUnit 4.12 runs test cases in parallel, so the envelope ID needs to be initiated as well.
	    
	 //  private JSON json = new JSON();
	    

	
	public static void main (String[] args){
		
		
                launch (args);
                
		
		
		
		
	}
        
    @Override
    public void start (Stage primaryStage) throws Exception {
        primaryStage.setTitle ("GPS Signing Beta");
        
        
        
        button1 = new Button ();
        Text txt = new Text ();
        txt.setText("Welcome. Please press begin");
        button1.setText ("Begin");
        button1.setOnAction (this);
        button1.setMinSize(100, 100);
        
        BorderPane p = new BorderPane ();
        p.setCenter (txt);
        p.setTop(button1);
  
        
        Scene scene = new Scene (p, 500, 500);
        primaryStage.setScene(scene);
        primaryStage.show();
        
        main m = new main();
        m.LoginTest();
		
        String GPS = m.getGPS();
        boolean check = m.GPSCheck(GPS);
		
        if (check == true){
            //m.EmbeddedSigningTest();
	}
    }
        
    @Override
    public void handle (ActionEvent event){
        
        if (event.getSource() == button1){
            System.out.println("I have been pressed");
        }
        
    }
	
	
	public String getGPS (){
		/*
		 * Acquire signal from GPS device 
		 */
		
		
		return "32.885, -117.239"; 
	}
	
	
	public boolean GPSCheck (String GPS) {
		
		/*
		 * Parse for two doubles (long and lat)
		 */
		
		double HQCoordX = 32.885320;
		double HQCoordY = -117.239718;
		
		int commaIndex = GPS.indexOf(",");
		String GPSx = GPS.substring(0,commaIndex);
		String GPSy = GPS.substring(commaIndex+2);
		Double GPSNumX = Double.parseDouble(GPSx);
		Double GPSNumY = Double.parseDouble(GPSy);
		
		System.out.println(GPSNumX);
		System.out.println(GPSNumY);
				
		
		
		if((GPSNumX <= (HQCoordX + 0.1)) && (GPSNumX >= (HQCoordX - 0.1)) 
				&& (GPSNumY <= (HQCoordY + 0.1)) && (GPSNumY >= (HQCoordY - 0.1))){
			return true;
		}
		return false;
	}
	
	
	public String createAuthHeaderCreds(String userName, String password, String integratorKey)
	   {
	       DocuSignCredentials dsCreds = new DocuSignCredentials(UserName, Password, IntegratorKey);
	        
	       String creds = null;
	       try
	       {
	           ObjectMapper mapper = new ObjectMapper();
	           creds= mapper.writeValueAsString(dsCreds);
	       }
	       catch (JsonProcessingException ex)
	       {
	           creds = "";
	       }
	        
	        
	       return creds;
	   }

	
	
	public void LoginTest() {
	        
	        ApiClient apiClient = new ApiClient();
	        apiClient.setBasePath(BaseUrl);
	        
	        String creds = createAuthHeaderCreds(UserName, Password, IntegratorKey);
	        apiClient.addDefaultHeader("X-DocuSign-Authentication", creds);
	        Configuration.setDefaultApiClient(apiClient);
	        
	        try
	        {
	            
	            AuthenticationApi authApi = new AuthenticationApi();
	            AuthenticationApi.LoginOptions loginOps = authApi.new LoginOptions();
	            loginOps.setApiPassword("true");
	            loginOps.setIncludeAccountIdGuid("true");
	            LoginInformation loginInfo = authApi.login(loginOps);
	            
	          
	            List<LoginAccount> loginAccounts = loginInfo.getLoginAccounts();
	            
	            
	            System.out.println("LoginInformation: " + loginInfo);
	        }
	        catch (ApiException ex)
	        {
	            System.out.println("Exception: " + ex);
	        }
	    }

	
	public void EmbeddedSigningTest()
    {
        byte[] fileBytes = null;
        try
        {
            //  String currentDir = new java.io.File(".").getCononicalPath();
            
            String currentDir = System.getProperty("user.dir");
            
            Path path = Paths.get(currentDir + SignTest1File);
            fileBytes = Files.readAllBytes(path);
        }
        catch (IOException ioExcp)
        {
            
        }
        
        
        
        // create an envelope to be signed
        EnvelopeDefinition envDef = new EnvelopeDefinition();
        envDef.setEmailSubject("Please Sign my Java SDK Envelope (Embedded Signer)");
        envDef.setEmailBlurb("Hello, Please sign my Java SDK Envelope.");
        
        
        
        // add a document to the envelope
        Document doc = new Document();
        String base64Doc = Base64.getEncoder().encodeToString(fileBytes);
        doc.setDocumentBase64(base64Doc);
        doc.setName("TestFile.pdf");
        doc.setDocumentId("1");
        
        List<Document> docs = new ArrayList<Document>();
        docs.add(doc);
        envDef.setDocuments(docs);
        
        // Add a recipient to sign the document
        Signer signer = new Signer();
        signer.setEmail(UserName);
        String name = "Pat Developer";
        signer.setName(name);
        signer.setRecipientId("1");
        
        // this value represents the client's unique identifier for the signer
        String clientUserId = "2939";
        signer.setClientUserId(clientUserId);
        
        // Create a SignHere tab somewhere on the document for the signer to sign
        SignHere signHere = new SignHere();
        signHere.setDocumentId("1");
        signHere.setPageNumber("1");
        signHere.setRecipientId("1");
        signHere.setXPosition("100");
        signHere.setYPosition("100");
        
        List<SignHere> signHereTabs = new ArrayList<SignHere>();
        signHereTabs.add(signHere);
        Tabs tabs = new Tabs();
        tabs.setSignHereTabs(signHereTabs);
        signer.setTabs(tabs);
        
        // Above causes issue
        envDef.setRecipients(new Recipients());
        envDef.getRecipients().setSigners(new ArrayList<Signer>());
        envDef.getRecipients().getSigners().add(signer);
        
        // send the envelope (otherwise it will be "created" in the Draft folder
        envDef.setStatus("sent");
        
        
        try
        {
            
            ApiClient apiClient = new ApiClient();
            apiClient.setBasePath(BaseUrl);
            
            String creds = createAuthHeaderCreds(UserName, Password, IntegratorKey);
            apiClient.addDefaultHeader("X-DocuSign-Authentication", creds);
            Configuration.setDefaultApiClient(apiClient);
            
            AuthenticationApi authApi = new AuthenticationApi();
            LoginInformation loginInfo = authApi.login();
            
           
            List<LoginAccount> loginAccounts = loginInfo.getLoginAccounts();
           
            
            String accountId = loginInfo.getLoginAccounts().get(0).getAccountId();
            
            EnvelopesApi envelopesApi = new EnvelopesApi();
            EnvelopeSummary envelopeSummary = envelopesApi.createEnvelope(accountId, envDef);
            
            
            
            System.out.println("EnvelopeSummary: " + envelopeSummary);
            
            String returnUrl = "http://www.docusign.com/developer-center";
            RecipientViewRequest recipientView = new RecipientViewRequest();
            recipientView.setReturnUrl(returnUrl);
            recipientView.setClientUserId(clientUserId);
            recipientView.setAuthenticationMethod("email");
            recipientView.setUserName(name);
            recipientView.setEmail(UserName);
            
            ViewUrl viewUrl = envelopesApi.createRecipientView(loginInfo.getLoginAccounts().get(0).getAccountId(), envelopeSummary.getEnvelopeId(), recipientView);
            
           
            
            // This Url should work in an Iframe or browser to allow signing
            System.out.println(viewUrl.url);

            try {
                Desktop desktop = java.awt.Desktop.getDesktop();
                URI oURL = new URI(viewUrl.url);
               desktop.browse(oURL);
            } catch (Exception e) {
                e.printStackTrace();
            }
            
        }
        catch (ApiException ex)
        {
            System.out.println("Exception: " + ex);
           
        }
        
    }    

	
	
	
}