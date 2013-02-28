require 'rubygems'
require 'dm-core'

# Basic model
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

# TODO point to subdir libs
