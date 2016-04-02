
package components;

import javafx.scene.control.TextField;

/**
 * The NumericTextField class represents an input component that allows a user only to enter numeric values.
 * @author ardkastrati
 * @version 1.0
 * @see TextField
 */
public class NumericTextField extends TextField {

	@Override
	public void replaceText(int start, int end, String text) {
		if (validate(text)) {
			super.replaceText(start, end, text);
		}
	}

	@Override
	public void replaceSelection(String text) {
		if (validate(text)) {
			super.replaceSelection(text);
		}
	}
        
	// Returns true if the text contains numbers
	private boolean validate(String text) {
		return text.matches("[0-9]*");
	}
}