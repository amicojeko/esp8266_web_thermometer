#models.rb
class Config < ActiveRecord::Base
  class << self
    def switch(id)
      find_or_create_by(key: "switch_#{id}")
    end
  end
end
