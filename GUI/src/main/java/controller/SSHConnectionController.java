package controller;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;
import com.jcraft.jsch.UIKeyboardInteractive;
import com.jcraft.jsch.UserInfo;
import components.NumericTextField;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.PathTransition;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.CubicCurveTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;
import model.Shell;

public class SSHConnectionController extends BodyController implements Initializable {
  
    
    @FXML
    private TextField server;
    @FXML
    private TextField username;
    @FXML
    private PasswordField password;
    @FXML
    private NumericTextField port;
   
    @FXML
    private AnchorPane anchorpane;
    
    
    
     @FXML
    private void connect(ActionEvent event) {
         JSch shell = new JSch();
        try {
            
            Session session = shell.getSession(username.getText(), server.getText(), port.getPort());
            session.setPassword(password.getText());
            UserInfo ui = new Shell.MyUserInfo(){
                public void showMessage(String message){
                    System.out.println(message);
                }
                public boolean promptYesNo(String message){
                    
                    System.out.println(message);
                    Scanner in = new Scanner(System.in);
                    String answer = in.next();
                    return answer.equals("yes") ? true : false;
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
        }
        
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
   

    @FXML
    private void handleSSHAction(ActionEvent event) {
        
/*        if(event.getSource() == connect) {
            try {
                System.out.println(username.getText());
                anchorpane.getChildren().clear();
                Thread.sleep(2000);
                final Circle circle = new Circle (40);
                
                
                circle.setFill(Color.ORANGE);
               //rectPath.setArcHeight(10);
               // rectPath.setArcWidth(10);
               // rectPath.setFill(Color.ORANGE);
                Path path = new Path();
                
                path.getElements().add(new MoveTo(20,20));
                path.getElements().add(new CubicCurveTo(30, 10, 380, 120, 200, 120));
                path.getElements().add(new CubicCurveTo(0, 120, 0, 240, 380, 240));
                PathTransition pathTransition = new PathTransition();
                pathTransition.setDuration(Duration.millis(4000));
                pathTransition.setPath(path);
                pathTransition.setNode(circle);
                pathTransition.setOrientation(PathTransition.OrientationType.ORTHOGONAL_TO_TANGENT);
                pathTransition.setCycleCount(Timeline.INDEFINITE);
                pathTransition.setAutoReverse(true);
                anchorpane.getChildren().add(path);
                anchorpane.getChildren().add(circle);
                pathTransition.play();
                
                
                
                //controller.changeBody();    
            } catch (InterruptedException ex) {
                Logger.getLogger(SSHConnectionController.class.getName()).log(Level.SEVERE, null, ex);
            }
        } else if (event.getSource() == cancel) {
            System.out.println(password.getText());
        }
        */
    }
    
    public void init(MainSceneController controller) {
        this.controller = controller;
    }
    
    
    
    
    
     public static abstract class MyUserInfo implements UserInfo, UIKeyboardInteractive {
            
         public String getPassword(){ return null; }
            public boolean promptYesNo(String str){ return false; }
            public String getPassphrase(){ return null; }
            public boolean promptPassphrase(String message){ return false; }
            public boolean promptPassword(String message){ return false; }
            public void showMessage(String message){ }
            public String[] promptKeyboardInteractive(String destination, 
                                                      String name, String instruction, 
                                                      String[] prompt, boolean[] echo){
                return null;
            }
    }
}
