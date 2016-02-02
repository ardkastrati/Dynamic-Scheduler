/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import controller.MainSceneController;
import javafx.fxml.FXML;

/**
 *
 * @author ardkastrati
 */
public abstract class BodyController {
 
    protected MainSceneController controller;
    
    public abstract void init(MainSceneController parentController);
}
