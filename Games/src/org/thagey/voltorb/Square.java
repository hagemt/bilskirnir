package org.thagey.voltorb;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

public class Square extends JPanel {
	public static enum Value { ZERO, ONE, TWO, THREE; };
	private static final long serialVersionUID = 5371573792895076321L;
	private JButton button;
	private Value number;
	
	public Square() { this(0); }
	
	public Square(int value) {
		this.setPreferredSize(new Dimension(48, 48));
		button = new JButton();
		button.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent e) {
				button.setText(Integer.toString(number.ordinal()));
			}
		});
		this.add(button);
		try {
			number = Value.values()[value];
		} catch (IndexOutOfBoundsException ioobe) {
			throw new IllegalArgumentException("Cannot create a square with value: " + value);
		}
	}
	
	public int getNumber() {
		return number.ordinal();
	}
}
