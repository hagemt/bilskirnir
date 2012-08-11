package org.thagey.voltorb;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.SwingConstants;

/**
 * @author Tor E Hagemann <hagemt@rpi.edu>
 */
public class Interface extends JFrame implements SwingConstants {
	private static final long serialVersionUID = 1489414536480641303L;
	private static final int POSSIBLE_VALUES = 4;
	private int[][] points;
	private JButton solveButton;
	
	public Interface(int h, int w) {
		points = new int[h][w];
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				points[i][j] = (int)(Math.random() * POSSIBLE_VALUES);
			}
		}
		solveButton = new JButton("!");
		solveButton.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(Interface.this, "What do you want?");
			}
		});
		this.setLayout(new GridLayout(h + 1, w + 1));
		for (int i = 0; i < points.length; ++i) {
			int sumPoints = 0, numZeroes = 0;
			for (int j = 0; j < points[i].length; ++j) {
				int value = points[i][j];
				if (value == 0) { ++numZeroes; }
				sumPoints += value;
				this.add(new Square(value));
			}
			this.add(new JLabel(Integer.toString(sumPoints) + "," + Integer.toString(numZeroes)));
		}
		for (int i = 0; i < w; ++i) {
			int sumPoints = 0, numZeroes = 0;
			for (int j = 0; j < h; ++j) {
				int value = points[j][i];
				if (value == 0) { ++numZeroes; }
				sumPoints += value;
			}
			this.add(new JLabel(Integer.toString(sumPoints) + "," + Integer.toString(numZeroes)));
		}
		this.add(solveButton);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setTitle("Voltorb Flip v0.0");
		this.setResizable(false);
		this.pack();
	}

	public static void main(String... args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new Interface(5, 5).setVisible(true);
			}
		});
	}
}
