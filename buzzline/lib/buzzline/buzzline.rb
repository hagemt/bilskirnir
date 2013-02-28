# Author::    Tor E Hagemann <hagemt@rpi.edu>
# Copyright:: Copyright (c) 2012 onetooneandonto

require 'rubygems'
require 'dm-core'

# Buzzline Model

module Buzzline
	class Buzzline
		include DataMapper::Resource
		property :id, Serial
		property :date, String
		property :email, String
		property :who, String
		property :when, String
		property :what, String
		property :where, String
		property :why, String
		property :how, String
	end
end

# FIXME REMOVE
#b = Buzzline.new
# TODO lawl WTF does this do?
#DataMapper.auto_upgrade!

# Buzzline Tests

require 'test/unit'

module Buzzline
	class BuzzlineUnitTestCase < Test::Unit::TestCase
		def setup
			@buzzline = Buzzline.new
		end
		def test_db
			raise "Cannot construct Buzzline" unless @buzzline
		end
	end
end
