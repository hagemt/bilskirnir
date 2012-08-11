package org.thagey.minesweeper;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Cell extends JPanel {
	public static final int BOMB_VALUE = -1;
	private static final long serialVersionUID = -386407104899226224L;
	private static final Icon icon = new ImageIcon(Cell.class.getResource("images/bomb.png"), "BOOM!");
	private int value;
	private JLabel label;
	
	public Cell(boolean bomb) {
		label = bomb ? new JLabel(icon) : new JLabel();
		label.setFont(new Font("Courier", Font.BOLD, 36));
		this.setValue(value = bomb ? BOMB_VALUE : 0);
		this.setLayout(new GridBagLayout());
		this.setBackground(Color.LIGHT_GRAY);
		this.setPreferredSize(new Dimension(48, 48));
		this.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		this.addMouseListener(new MouseListener() {
			@Override
			public void mouseClicked(MouseEvent e) { }
			@Override
			public void mouseEntered(MouseEvent e) {
				Cell.this.setBackground(Color.DARK_GRAY);
			}
			@Override
			public void mouseExited(MouseEvent e) {
				Cell.this.setBackground(Color.LIGHT_GRAY);
			}
			@Override
			public void mousePressed(MouseEvent e) { }
			@Override
			public void mouseReleased(MouseEvent e) { }
		});
		// TODO hide label?
		this.add(label);
	}
	
	public int getValue() {
		return value;
	}
	
	public void setValue(int i) {
		if (value != BOMB_VALUE) {
			label.setText(Integer.toString(value = i));
		}
	}
}
