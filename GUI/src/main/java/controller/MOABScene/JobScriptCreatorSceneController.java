package controller.MOABScene;

/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */

import controller.LoadSceneHelper;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Pagination;
import javafx.util.Callback;

/**
 * FXML Controller class
 *
 * @author ardkastrati
 */
public class JobScriptCreatorSceneController implements Initializable, CommandController {
 
    @FXML
    Pagination commandPages;
    
    private MsubController msubController;
    private MpirunSceneController mpirunController;
    private DirectoryChooserSceneController directoryChooserController;
    
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        setPages();
    } 
    
    private void setPages() {
        commandPages.setPageFactory(new Callback<Integer, Node>() {
            @Override
            public Node call(Integer pageIndex) {
               Node node = setPage(pageIndex);
               return node;
            }
        });
    }
    private Node setPage(int index) {
        
        LoadSceneHelper loaderHelper = new LoadSceneHelper();
        FXMLLoader loader = null;
       
        switch(index) {
            case 0: 
                loader = loaderHelper.loadScene("MSUB");
                msubController = loader.getController();
                break;
            case 1:
                 loader = loaderHelper.loadScene("MPIRUN");
                 mpirunController = loader.getController();
                 break;
            case 2:
                loader = loaderHelper.loadScene("DirectoryChooser");
                directoryChooserController = loader.getController();
                break;
            default:
                assert false : this;
                break;
        }
        
        Node node = null;
        try {
            node = loader.load();
        } catch (IOException ex) {
            Logger.getLogger(JobScriptCreatorSceneController.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return node;
    }

    

    @Override
    public void onCancelClicked() {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public FXMLLoader onExecuteClicked() {
        
        
        
        // throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        FXMLLoader loader = new FXMLLoader(ClassLoader.getSystemResource("fxml/JobScriptScene.fxml"));
        JobScriptSceneController controller = loader.getController();
        
        return loader;
    }

    @Override
    public String getOnExecuteText() {
       return "Generate Script";
    }
    
    public void test() {
        System.out.println(msubController.toString());
    }

   
}
