/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package components;

import javafx.scene.control.TextField;

/**
 *
 * @author ardkastrati
 */
public class NumericTextField extends TextField {
    
    @Override
    public void replaceText(int start, int end, String text){
        if (validate(text))
        {
            super.replaceText(start, end, text);
        }
    }

    @Override
    public void replaceSelection(String text){
        if (validate(text))
        {
            super.replaceSelection(text);
        }
    }
    
    public int getPort() {
        String port = super.getText();
        return Integer.parseInt(port);
   }

    private boolean validate(String text){
        return text.matches("[0-9]*");
    }
    
    
}