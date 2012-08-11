package org.thagey.minesweeper;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;

/**
 * @author Tor E Hagemann <hagemt@rpi.edu>
 */
public class Board extends JFrame implements SwingConstants {
	private static final long serialVersionUID = -674211347108796927L;
	private static final double BOMB_DENSITY = 0.1d;
	private int height, width;
	private Cell[][] cells;
	private JPanel board;
	private Timer timer;
	private int seconds;
	
	public Board(int h, int w) {
		if (h < 1 || w < 1) {
			throw new IllegalArgumentException("Invalid dimensions: " + h + "x" + w);
		}
		seconds = 0;
		height = h; width = w;
		board = new JPanel();
		cells = new Cell[height][width];
		timer = new Timer(1000, new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				++Board.this.seconds;
				Board.this.updateTimer();
			}
		});
		board.setBorder(BorderFactory.createTitledBorder("Board"));
		board.setLayout(new GridLayout(height, width, 1, 1));
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				board.add(cells[i][j] = new Cell(Math.random() < BOMB_DENSITY));
			}
		}
		this.getContentPane().add(board);
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		this.updateTimer();
		this.pack();
	}

	private void updateTimer() {
		int m = seconds / 60;
		int h = m / 60;
		int s = seconds % 60;
		StringBuilder sb = new StringBuilder("Minesweeper (");
		if (h > 0) { sb.append(h); sb.append(':'); }
		if (m < 10) { sb.append('0'); }
		sb.append(m);
		sb.append(':');
		if (s < 10) { sb.append('0'); }
		sb.append(s);
		this.setTitle(sb.append(")").toString());
	}

	public static void main(String... args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new Board(10, 10).setVisible(true);
			}
		});
	}
}
