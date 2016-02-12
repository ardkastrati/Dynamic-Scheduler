package controller.SSHConnectionScene;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;
import com.jcraft.jsch.UIKeyboardInteractive;
import com.jcraft.jsch.UserInfo;
import components.NumericTextField;
import controller.mainScene.MainSceneController;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.concurrent.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;


public class SSHConnectionController implements Initializable {
  
    
    @FXML
    private TextField serverField;
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private NumericTextField portField;
   
    @FXML
    private AnchorPane anchorpane;
    
    private Service service;
    
    private JSch jsch;
    private Session session;
    private ChannelSftp sftpChannel;
    
     @FXML
    private void connect(ActionEvent event) {
            
            
            String user = usernameField.getText();
            String host = serverField.getText();
            int port = Integer.parseInt(portField.getText());
            jsch = new JSch();
            
            try {
                session = jsch.getSession(user, host, port);
            } catch (JSchException ex) {
                System.out.println("Connection problem - Ard");
            }

            // username and password will be given via UserInfo interface.
            //UserInfo ui=new Sftp.MyUserInfo();
            session.setPassword(passwordField.getText());
            //session.setHost(host);
            //sessio
            java.util.Properties config = new java.util.Properties(); 
            config.put("StrictHostKeyChecking", "no");
            session.setConfig(config);
            
            //only to test!!!!
            MainSceneController.session = session;
            
            //Channel channel = null;
            
            try {
                 session.connect();
                 System.out.println("Connected");
                 //channel = session.openChannel("sftp");
                 //channel.connect();
                 //ChannelSftp c = (ChannelSftp)channel;
            } catch (JSchException ex) {
                System.out.println("Connection problem - Ard");
            }

            
           
      
         /*JSch shell = new JSch();
        try {
            
            Session session = shell.getSession(username.getText(), server.getText(), port.getPort());
            session.setPassword(password.getText());
            UserInfo ui = new .MyUserInfo(){
                @Override
                public void showMessage(String message){
                    System.out.println(message);
                }
                @Override
                public boolean promptYesNo(String message){
                    
                    System.out.println(message);
                    Scanner in = new Scanner(System.in);
                    String answer = in.next();
                    return answer.equals("yes");
                }
            };
            session.setUserInfo(null);
            
            session.connect(30000);
            
            Channel channel=session.openChannel("shell");
            
            channel.setInputStream(System.in);
            
            channel.setOutputStream(System.out);
            
            channel.connect(3*1000);
            
        } catch (JSchException ex) {
            Logger.getLogger(SSHConnectionController.class.getName()).log(Level.SEVERE, null, ex);
        }*/
        
    }
    
    public void initService(Service service) {
        this.service = service;
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
    }    
    
   
    
    
    public Session getSession() {
        return this.session;
    }
    
    
    
 

}
